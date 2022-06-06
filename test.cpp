
#include <thread>
#include <mutex>
#include <atomic>

#include "./nvToolsExt.h"

#include "c_random.h"
#include "test.h"
#include "c_particle_system.h"
#include "c_particle.h"
#include "c_effects_factory.h"

static std::atomic_int globalTime;//for calculating delta time
static std::atomic_bool workerMustExit = false;//notify that thread need to exit
static std::atomic_bool canRender(true);//notify that we are swapped buffers
static std::atomic_bool isRendering(true);//notify that we are started rendering
static std::mutex main_pool_lock;//for click-handle
static std::vector<c_effect>render_static_buffer;

static c_particle_system* g_particle_system = c_particle_system::get_instance();

void WorkerThread(void)
{
	while (!workerMustExit)
	{
		nvtxRangePush(__FUNCTION__);

		static int lastTime = 0;
		const int time = globalTime.load();
		const int delta = time - lastTime;
		lastTime = time;
		/*
		P.S - на проде - естественно бесполезный закоменченный код удаляется
		static int accum = 0;
		static int fps = 0;
		accum += delta;
		if (accum >= 1000) {
			printf("logic fps %d\n", fps);
			fps = 0;
			accum = 0;
		}
		*/
		if (delta > 0)
		{
			main_pool_lock.lock();//click -> adding to main pool -> guard this line
			g_particle_system->update(delta);
			main_pool_lock.unlock();
			canRender = false;//notify
			if (!isRendering.load()) {//to prevent interrupting the render
				const auto ptr_main_effects = &g_particle_system->get_pool();
				const auto ptr_back_effects = &g_particle_system->get_buffer();
				size_t size = ptr_main_effects->size();
				*ptr_back_effects = *ptr_main_effects;
				canRender = true;//notify that we are end
			}	
			//fps++;
		}
		static const int MIN_UPDATE_PERIOD_MS = 10;
		if (delta < MIN_UPDATE_PERIOD_MS)
			std::this_thread::sleep_for(std::chrono::milliseconds(MIN_UPDATE_PERIOD_MS - delta));

		nvtxRangePop();
	}
}
void test::init(void)
{
	c_random::initialize();
	g_particle_system->initialize();
	render_static_buffer.resize(MAX_EFFECTS);
	std::thread workerThread(WorkerThread);
	workerThread.detach(); // Glut + MSVC = join hangs in atexit()
}
void test::term(void)
{
	workerMustExit = true;
	g_particle_system->destroy();
	render_static_buffer.clear();
}
void test::render(void)
{
	if (canRender.load()) {
		isRendering = true;//prevent changing backbuffer
		render_static_buffer = g_particle_system->get_buffer();//update data
		isRendering = false;//notify that we are updated
	}//render old(or new) data
	for (c_effect& effect : render_static_buffer) {
		if (!effect.is_alive())continue;
		std::vector<c_particle>* particles = &effect.get_particles();
		for (c_particle& particle : *particles)
		{
			if (particle.is_disabled())continue;
			vec2& position = particle.get_position();
			auto& color = particle.get_color();
			platform::drawPoint(position.x(), test::SCREEN_HEIGHT - position.y(), color.r, color.g, color.b, color.a);
		}
	}
}

void test::update(int dt)
{
	globalTime.fetch_add(dt);
}

void test::on_click(int x, int y)
{
	c_effect effect = g_effect_factory->create_effect(x, y, globalTime);
	main_pool_lock.lock();                             
	g_particle_system->emit_effect(effect);
	main_pool_lock.unlock();
}
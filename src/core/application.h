#pragma once 
#include "window.h"
#include "layer_manager.h"

class Application
{
private:
	static Application* s_Instance;	

public:
	Application(const char* title, uint16_t width, uint16_t height, int window_flags);
	~Application();

	void run();

	uint64_t framerate() const;

	inline void addLayer(std::shared_ptr<Layer> layer) { m_LayerManager.addLayer(layer); }
	inline void removeLayer(std::shared_ptr<Layer> layer) { m_LayerManager.removeLayer(layer); }
	inline static Application& Get() { return *s_Instance; }
	inline Window& window() { return m_Window; }
	

	inline static void exit() { close_window(Get().m_Window); }

private:
	void onUpdate(float deltaTime);
	void onEvent(Event& e);

private:
	LayerManager m_LayerManager;
	Window m_Window;
};
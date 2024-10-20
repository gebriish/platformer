#include "layer_manager.h"
#include <functional>

LayerManager::LayerManager()
{}

LayerManager::~LayerManager()
{}

void LayerManager::addLayer(std::shared_ptr<Layer> layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
	m_LayerInsertIndex++;
	layer->onAttach();
}

void LayerManager::callUpdate(float deltaTime)
{
	for(auto& l : m_Layers)
		l->onUpdate(deltaTime);
}

void LayerManager::removeLayer(std::shared_ptr<Layer> layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
	if (it != m_Layers.begin() + m_LayerInsertIndex)
	{
		layer->onDetach();
		m_Layers.erase(it);
		m_LayerInsertIndex--;
	}
}

void LayerManager::cleanup()
{
	for(auto& l : m_Layers)
		l->onDetach();
	m_LayerInsertIndex = 0;
	m_Layers.clear();
}

void LayerManager::dispatchEvent(const Event& e)
{
	for(auto& l : m_Layers)
		l->onEvent(e);
}
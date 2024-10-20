#pragma once
#include <vector>
#include <memory>
#include <cstdint>
#include "layer.h"

class LayerManager
{
public:
	LayerManager();
	~LayerManager();

	void addLayer(std::shared_ptr<Layer> layer);
	void callUpdate(float deltaTime);
	void removeLayer(std::shared_ptr<Layer> layer);
	
	void cleanup();

	void dispatchEvent(const Event& e);

	inline size_t listSize() const { return m_Layers.size(); }

	std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
	std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }

private:
	std::vector<std::shared_ptr<Layer>> m_Layers;
	uint32_t m_LayerInsertIndex = 0;
};
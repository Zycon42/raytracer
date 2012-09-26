#pragma once

class Renderable;
class Light;

#include <vector>
#include <memory>

class Scene
{
public:
	typedef std::vector<std::shared_ptr<Renderable>> RenderableList;
	typedef std::vector<std::shared_ptr<Light>> LightList;

	Scene();

	RenderableList& renderables() { return _renderables; }
	LightList& lights() { return _lights; }
private:
	RenderableList _renderables;
	LightList _lights;
};

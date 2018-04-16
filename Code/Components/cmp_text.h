#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>
#include "system_renderer.h"

class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, const std::string& str = "");
	void Update(const double &dt) override;

	void render() override;

	void SetRenderLayer(Renderer::Layer l) { renderLayer = l; }
	~TextComponent() override = default;

	void SetText(const std::string& str);

protected:
	Renderer::Layer renderLayer = Renderer::Layer::UIMID;
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};

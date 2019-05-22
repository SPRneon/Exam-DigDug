#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include "BaseComponent.h"
#include "MathHelper.h"

namespace dae{
	class TextObject;

	class Font;
	class TextComponent final : public BaseComponent
	{
public:
		void Update() override;
		void Draw() const override;
		void Initialize() override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(float r, float g, float b);
		void SetColor(Color color);
		void SetNeedsUpdate(bool needsUpdate){m_NeedsUpdate = needsUpdate;}
		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font, Color color =  Colors::white);
		virtual ~TextComponent() = default;

		//disabling default and copy
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

private:
	bool m_IsWorldSpace = false;
	bool m_IsScreenSpace = true;
	glm::vec2 m_ScreenPos = glm::vec2(0.f,0.f);
	Color m_TextColor = Colors::white;
	bool m_NeedsUpdate;
	std::shared_ptr<Font> m_pFont;
	std::shared_ptr<Texture2D> m_pTexture;
	std::string m_Text;
	};
}


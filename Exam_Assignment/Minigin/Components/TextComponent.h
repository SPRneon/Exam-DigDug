#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "BaseComponent.h"

namespace dae{
	class TextObject;

	class Font;
	class TextComponent final : public BaseComponent
	{
public:
		void Update() override;
		void Draw() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);


		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;

		//disabling default and copy
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

private:
	bool m_IsWorldSpace = false;
	bool m_IsScreenSpace = true;
	glm::vec3 m_ScreenPos = glm::vec3(0.f,0.f,0.f);
	bool m_NeedsUpdate;
	std::shared_ptr<Font> m_pFont;
	std::shared_ptr<Texture2D> m_pTexture;
	std::string m_Text;
	};
}


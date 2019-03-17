#pragma once
#include "SceneObject.h"
#include "Components\TransformComponent.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextObject : public SceneObject
	{
	public:
		void Update() override;
		void Draw() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);


		explicit TextObject(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:


		bool mNeedsUpdate;
		std::string mText;
		TransformComponent* m_pTransform;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;
	};

}

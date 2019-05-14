#pragma once
#include "BaseComponent.h"


namespace dae{


	class Texture2D;
class TextureComponent final : public BaseComponent
{
public:
	void Update() override;
	void Draw() const override;
	void Initialize() override;


	void SetTexture(std::shared_ptr<Texture2D> pTexture);
	void SetPosition(float x, float y);

	explicit TextureComponent(const std::string& path);
	virtual ~TextureComponent() = default;
private:
	std::shared_ptr<Texture2D> m_pTexture;

	glm::vec3 m_TexturePos;
};
}


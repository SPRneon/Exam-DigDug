#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae{


class Texture2D;
class TextureComponent final : public BaseComponent
{
public:
	void Update() override;
	void Draw() const override;
	void Initialize() override;


	void SetTexture(std::shared_ptr<Texture2D> pTexture, int nrOfSprites = 1);
	void SetTexture(const std::string & path, int nrOfSprites = 1);
	void SetPosition(float x, float y);

	explicit TextureComponent(const std::string& path,int nrOfSprites = 1, float animSpeed = 1.0f);
	virtual ~TextureComponent() = default;
private:
	std::shared_ptr<Texture2D> m_pTexture;
	int m_NrOfSprites;
	int currSprites = 0;
	float m_AnimSpeed;
	float m_DeltaTime = 0;

	glm::vec2 m_ClipWH;
	glm::vec2 m_TexturePos;
};
}


#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <SDL.h>
#include "MathHelper.h"

namespace dae{


	class Texture2D;
class TextureComponent final : public BaseComponent
{
public:
	explicit TextureComponent(const std::string& path,int nrOfSprites = 1, float animSpeed = 1.0f, bool autoPlay = true);
	virtual ~TextureComponent(){m_pGameObject = nullptr;};

	void Update() override;
	void Draw() const override;
	void Initialize() override;


	void SetTexture(std::shared_ptr<Texture2D> pTexture, int nrOfSprites = 1);
	void SetTexture(const std::string & path, int nrOfSprites = 1);
	void SetPosition(float x, float y);
	void SetAnimSpeed(float animSpeed){m_AnimSpeed = animSpeed;}
	void Translate(float x, float y){m_TexturePos.x += x; m_TexturePos.y += y;}
	void SetDir(Direction dir){m_Direction = dir;};
	void Pause(){m_Play = false;}
	void Play(){m_Play = true;}

	void Show(){m_Show = true;}
	void Hide(){m_Show = false;}
	bool IsShown() const{return m_Show;}

	std::string GetOriPath() const {return m_OriginalPath;}

	void NextFrame(){currSprites++; currSprites %= m_NrOfSprites;}
	void PrevFrame(){currSprites--; if(currSprites == -1) currSprites = m_NrOfSprites-1;}
private:
	std::shared_ptr<Texture2D> m_pTexture;
	int m_NrOfSprites;
	int currSprites = 0;
	float m_AnimSpeed;
	float m_DeltaTime = 0;
	Direction m_Direction = RIGHT;
	bool m_Play = true;
	bool m_Show = true;

	std::string m_OriginalPath;
	glm::vec2 m_ClipWH;
	glm::vec2 m_TexturePos;
};
}


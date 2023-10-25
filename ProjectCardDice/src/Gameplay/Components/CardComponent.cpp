#include "CardComponent.h"
#include "../../Game.h"
#include "../../Core/EC/Entity.h"
#include "../../Core/Managers/TextureManager.h"

const Vector2D CardComponent::DEFAULT_CARD_SIZE = { 250, 375 };

const std::unordered_map<CardCategory, SDL_Color> CardComponent::CARD_CATEGORY_COLORS = {
	{ CardCategory::PYRO, { 255, 0, 30, 255 } },
	{ CardCategory::HYDRO, { 0, 50, 100, 255 } },
	{ CardCategory::GEO, { 140, 115, 85, 255 } },
	{ CardCategory::TEMPEST, { 180, 230, 230, 255 } },
	{ CardCategory::SHADOW, { 190, 255, 190, 255 } },
	{ CardCategory::ALCHEMY, { 128, 140, 0, 255 } },
	{ CardCategory::HOLY, { 255, 255, 210, 255 } },
	{ CardCategory::NECRO, { 20, 50, 20, 255 } },
	{ CardCategory::HEXER, { 128, 0, 128, 255 } },
	{ CardCategory::NEUTRAL, { 200, 200, 200, 255 } }
};

CardComponent::CardComponent(CardConfiguration cardConfiguration) : _cardConfiguration { cardConfiguration }, _transform { nullptr }, 
_destinationRect { 0, 0, 0, 0 }, _cardCategoryColor { 120, 120, 120, 255 }
{
}

CardComponent::~CardComponent()
{
}

void CardComponent::Init()
{
	std::cout << *this << std::endl;

	_cardCategoryColor = CARD_CATEGORY_COLORS.at(_cardConfiguration.cardCategory);

	// Initialize transform component
	_transform = &_owner->GetComponent<TransformComponent>();
	_transform->size = DEFAULT_CARD_SIZE;

	// Create textures and fonts for the card
	_thumbnailTexture.reset(TextureManager::LoadTexture(_cardConfiguration.thumbnailPath));
	_costFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 36, std::to_string(_cardConfiguration.cost).c_str()));
	_nameFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 26, _cardConfiguration.name.c_str()));
	_descriptionFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 20, _cardConfiguration.description.c_str(), false, 2, 222));
}

void CardComponent::Update(const float deltaTime)
{
	_destinationRect = _transform->GetDestinationRect();
}

void CardComponent::Render()
{
	RenderCardBackground();
	RenderCardThumbnail();
	RenderCardName();
	RenderCardCost();
	RenderCardDescription();
}

void CardComponent::RenderCardBackground() const
{
	// Render fill rect that will serve as the border of the card once all other elements are rendered on top of it
	SDL_SetRenderDrawColor(Game::renderer, _cardCategoryColor.r, _cardCategoryColor.g, _cardCategoryColor.b, _cardCategoryColor.a);
	SDL_RenderFillRect(Game::renderer, &_destinationRect);
}

void CardComponent::RenderCardThumbnail() const
{
	// Render thumbnail below the card name
	SDL_Rect thumbnailRect = { 
		_destinationRect.x + static_cast<int>(6 * _transform->scale), 
		_destinationRect.y + static_cast<int>(69 * _transform->scale),
		_destinationRect.w - static_cast<int>(12 * _transform->scale),
		static_cast<int>(162 * _transform->scale)
	};
	TextureManager::RenderTexture(_thumbnailTexture.get(), &thumbnailRect);

	// Render border around the thumbnail
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &thumbnailRect);
}

void CardComponent::RenderCardName() const
{
	// Render name background and border on top of the card
	SDL_Rect nameBackgroundRect = {
		_destinationRect.x + static_cast<int>(6 * _transform->scale),
		_destinationRect.y + static_cast<int>(6 * _transform->scale),
		_destinationRect.w - static_cast<int>(12 * _transform->scale),
		static_cast<int>(56 * _transform->scale)
	};
	SDL_SetRenderDrawColor(Game::renderer, static_cast<Uint8>(_cardCategoryColor.r * 1.5f), static_cast<Uint8>(_cardCategoryColor.g * 1.5f),
		static_cast<Uint8>(_cardCategoryColor.b * 1.5f), _cardCategoryColor.a);
	SDL_RenderFillRect(Game::renderer, &nameBackgroundRect);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);	
	SDL_RenderDrawRect(Game::renderer, &nameBackgroundRect);

	// Render card name on top of the background above and make sure it's centered horizontally and vertically
	SDL_Rect nameFontRect = { 
		_destinationRect.x + (_destinationRect.w / 2) - static_cast<int>(_nameFont.get()->width * _transform->scale / 2),
		_destinationRect.y + static_cast<int>(18 * _transform->scale),
		static_cast<int>(_nameFont.get()->width * _transform->scale),
		static_cast<int>(_nameFont.get()->height * _transform->scale)
	};
	TextureManager::RenderTexture(_nameFont.get()->texture, &nameFontRect);
}

void CardComponent::RenderCardCost() const
{
	// Render cost background and border on top left of the card
	SDL_Rect costBackgroundRect = { 
		_destinationRect.x - static_cast<int>(15 * _transform->scale),
		_destinationRect.y - static_cast<int>(23 * _transform->scale),
		static_cast<int>(38 * _transform->scale),
		static_cast<int>(38 * _transform->scale)
	};
	SDL_SetRenderDrawColor(Game::renderer, 0, 155, 255, 255);
	SDL_RenderFillRect(Game::renderer, &costBackgroundRect);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &costBackgroundRect);

	// Render card cost on top of the background above and make sure it's centered horizontally and vertically
	SDL_Rect costFontRect = { 
		_destinationRect.x + static_cast<int>(4 * _transform->scale - (_costFont.get()->width * _transform->scale / 2)),
		_destinationRect.y - static_cast<int>(25 * _transform->scale), 
		static_cast<int>(_costFont.get()->width * _transform->scale),
		static_cast<int>(_costFont.get()->height * _transform->scale)
	};
	TextureManager::RenderTexture(_costFont.get()->texture, &costFontRect);
}

void CardComponent::RenderCardDescription() const
{
	// Render description background and border below the thumbnail
	SDL_Rect descriptionBackgroundRect = { 
		_destinationRect.x + static_cast<int>(6 * _transform->scale),
		_destinationRect.y + static_cast<int>(237 * _transform->scale),
		_destinationRect.w - static_cast<int>(12 * _transform->scale),
		static_cast<int>(131 * _transform->scale)
	};
	SDL_SetRenderDrawColor(Game::renderer, static_cast<Uint8>(_cardCategoryColor.r * 1.5f), static_cast<Uint8>(_cardCategoryColor.g * 1.5f),
		static_cast<Uint8>(_cardCategoryColor.b * 1.5f), _cardCategoryColor.a);
	SDL_RenderFillRect(Game::renderer, &descriptionBackgroundRect);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(Game::renderer, &descriptionBackgroundRect);

	// Render card description on top of the background above
	SDL_Rect descFontRect = { 
		_destinationRect.x + static_cast<int>(15 * _transform->scale),
		_destinationRect.y + static_cast<int>(244 * _transform->scale),
		static_cast<int>(_descriptionFont.get()->width * _transform->scale),
		static_cast<int>(_descriptionFont.get()->height * _transform->scale)
	};
	TextureManager::RenderTexture(_descriptionFont.get()->texture, &descFontRect);
}

std::ostream& operator<<(std::ostream& os, const CardComponent& card)
{
	os << "CardComponent: " << card._cardConfiguration.name << " | " << card._cardConfiguration.description.substr(0, 20) << "..." << " | " 
		<< card._cardConfiguration.diceRoll.first << "d" << card._cardConfiguration.diceRoll.second << " + " <<
		card._cardConfiguration.diceModifiers.first << "d" << card._cardConfiguration.diceModifiers.second << " | " << "CardCategory: " <<
		static_cast<int>(card._cardConfiguration.cardCategory) << " | " << "TargetType: " << static_cast<int>(card._cardConfiguration.targetType) 
		<< " | " << "Costs: " << card._cardConfiguration.cost;

	return os;
}

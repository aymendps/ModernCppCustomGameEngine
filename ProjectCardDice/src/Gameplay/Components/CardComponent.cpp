#include "CardComponent.h"
#include "../../Game.h"
#include "../../Core/EC/Entity.h"
#include "../../Core/Managers/TextureManager.h"

const Vector2D CardComponent::DEFAULT_CARD_SIZE = { 200, 300 };

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

	_transform = &_owner->GetComponent<TransformComponent>();
	_transform->size = DEFAULT_CARD_SIZE;
	_cardCategoryColor = CARD_CATEGORY_COLORS.at(_cardConfiguration.cardCategory);

	// Create textures and fonts for the card
	_thumbnailTexture.reset(TextureManager::LoadTexture(_cardConfiguration.thumbnailPath));
	_costFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 30, std::to_string(_cardConfiguration.cost).c_str()));
	_nameFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 20, _cardConfiguration.name.c_str()));
	_descriptionFont.reset(TextureManager::LoadFontTexture(FontFamily::Arial, 16, _cardConfiguration.description.c_str(), false, 1, 178));
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
	// Render border around the thumbnail
	SDL_Rect thumbnailBorderRect = { _destinationRect.x + 5, _destinationRect.y + 50, _destinationRect.w - 10, 140 };
	SDL_SetRenderDrawColor(Game::renderer, _cardCategoryColor.r, _cardCategoryColor.g, _cardCategoryColor.b, _cardCategoryColor.a);
	SDL_RenderFillRect(Game::renderer, &thumbnailBorderRect);

	// Render thumbnail below the card name
	SDL_Rect thumbnailRect = { _destinationRect.x + 5, _destinationRect.y + 55, _destinationRect.w - 10, 130 };
	TextureManager::RenderTexture(_thumbnailTexture.get(), &thumbnailRect);
}

void CardComponent::RenderCardName() const
{
	// Render name background on top of the card
	SDL_Rect nameBackgroundRect = { _destinationRect.x + 5, _destinationRect.y + 5, _destinationRect.w - 10, 45 };
	SDL_SetRenderDrawColor(Game::renderer, static_cast<Uint8>(_cardCategoryColor.r * 1.5f), static_cast<Uint8>(_cardCategoryColor.g * 1.5f),
		static_cast<Uint8>(_cardCategoryColor.b * 1.5f), _cardCategoryColor.a);
	SDL_RenderFillRect(Game::renderer, &nameBackgroundRect);

	// Render card name on top of the background above and make sure it's centered horizontally and vertically
	SDL_Rect nameFontRect = { _destinationRect.x + (_destinationRect.w / 2) - (_nameFont.get()->width / 2)
		, _destinationRect.y + 15, _nameFont.get()->width, _nameFont.get()->height};
	TextureManager::RenderTexture(_nameFont.get()->texture, &nameFontRect);
}

void CardComponent::RenderCardCost() const
{
	// Render cost background on top left of the card
	SDL_Rect costBackgroundRect = { _destinationRect.x - 12, _destinationRect.y - 18, 30, 30 };
	SDL_SetRenderDrawColor(Game::renderer, 0, 155, 255, 255);
	SDL_RenderFillRect(Game::renderer, &costBackgroundRect);

	// Render card cost on top of the background above and make sure it's centered horizontally and vertically
	SDL_Rect costFontRect = { _destinationRect.x - 12 + (30 / 2) - (_costFont.get()->width / 2),
		_destinationRect.y - 20, _costFont.get()->width, _costFont.get()->height };
	TextureManager::RenderTexture(_costFont.get()->texture, &costFontRect);
}

void CardComponent::RenderCardDescription() const
{
	// Render description background below the thumbnail
	SDL_Rect descriptionBackgroundRect = { _destinationRect.x + 5, _destinationRect.y + 190, _destinationRect.w - 10, 105 };
	SDL_SetRenderDrawColor(Game::renderer, static_cast<Uint8>(_cardCategoryColor.r * 1.5f), static_cast<Uint8>(_cardCategoryColor.g * 1.5f),
		static_cast<Uint8>(_cardCategoryColor.b * 1.5f), _cardCategoryColor.a);
	SDL_RenderFillRect(Game::renderer, &descriptionBackgroundRect);

	// Render card description on top of the background above
	SDL_Rect descFontRect = { _destinationRect.x + 12, _destinationRect.y + 195, _descriptionFont.get()->width, _descriptionFont.get()->height };
	TextureManager::RenderTexture(_descriptionFont.get()->texture, &descFontRect);
}

std::ostream& operator<<(std::ostream& os, const CardComponent& card)
{
	os << "CardComponent: " << card._cardConfiguration.name << " | " << card._cardConfiguration.description << " | " <<
		card._cardConfiguration.diceRoll.first << "d" << card._cardConfiguration.diceRoll.second << " + " <<
		card._cardConfiguration.diceModifiers.first << "d" << card._cardConfiguration.diceModifiers.second << " | " << "CardCategory: " <<
		static_cast<int>(card._cardConfiguration.cardCategory) << " | " << "TargetType: " << static_cast<int>(card._cardConfiguration.targetType) 
		<< " | " << "Costs: " << card._cardConfiguration.cost;

	return os;
}

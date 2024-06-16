#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/SecretRewardsLayer.hpp>
#include "TreasureCheckAlert.hpp"

using namespace geode::prelude;

// Garage Layer
class $modify(GarageLayer, GJGarageLayer){
	bool init(){
		if (!GJGarageLayer::init()) return false;
		auto removedButton = Mod::get()->getSettingValue<bool>("remove-button");

		if(!removedButton){
			NodeIDs::provideFor(this);

			auto menu = this->getChildByID("shards-menu");

			auto spr = CircleButtonSprite::createWithSpriteFrameName("chest_03_02_001.png", 1, CircleBaseColor::Gray, CircleBaseSize::Small);
			auto button = CCMenuItemSpriteExtra::create(
				spr,
				this,
				menu_selector(GarageLayer::onChestButton));
			button->setID("Treasure-Checklist-Button");
			
			menu->addChild(button);
			menu->updateLayout();
		}

		return true;
	}

	void onChestButton(CCObject *){
		TreasureCheckAlert::create()->show();
	}
};

// Treasure Room Layer
class $modify(TreasureRoomLayer, SecretRewardsLayer){
	bool init(bool p0){
		if(!SecretRewardsLayer::init(p0)) return false;
		auto winSize = CCDirector::sharedDirector()->getWinSize();

		NodeIDs::provideFor(this);

		auto menu = CCMenu::create();
		menu->setPosition({30.0f, 30.0f});
		menu->setID("Treasure-Checklist-Menu");
		menu->setZOrder(5);
		
		auto button = CCMenuItemSpriteExtra::create(
			CCSprite::create("ModInfoIcon.png"_spr),
			this,
			menu_selector(TreasureRoomLayer::onChestButton));
		button->setID("Treasure-Checklist-Button");
		
		menu->addChild(button);
		menu->updateLayout();
		this->addChild(menu);
		return true;
	}

	void onChestButton(CCObject *){
		TreasureCheckAlert::create()->show();
	}
};
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include "TreasureCheckAlert.hpp"

using namespace geode::prelude;

//	The Mod modifies the Garage Layer to add the new Button.
class $modify(ModLayer, GJGarageLayer){
	bool init(){
		if (!GJGarageLayer::init()) return false;

		NodeIDs::provideFor(this);

		auto menu = this->getChildByID("shards-menu");

		auto spr = CircleButtonSprite::createWithSpriteFrameName("chest_03_02_001.png", 1, CircleBaseColor::Gray, CircleBaseSize::Small);
		auto button = CCMenuItemSpriteExtra::create(
			spr,
			this,
			menu_selector(ModLayer::onChestButton));
		button->setID("Treasure-Checklist-Button");
		
		menu->addChild(button);
		menu->updateLayout();
		return true;
	}

	void onChestButton(CCObject *){
		TreasureCheckAlert::create()->show();
	}
};
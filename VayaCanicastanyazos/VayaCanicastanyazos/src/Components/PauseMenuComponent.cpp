#include "PauseMenuComponent.h"
#include "MotorCasaPaco.h"
#include "Input/InputManager.h"
#include "Audio/AudioManager.h"

PauseMenuComponent::PauseMenuComponent(json& args): Component(args)
{

}

PauseMenuComponent::~PauseMenuComponent()
{
	Component::~Component();
}

bool PauseMenuComponent::ReceiveEvent(Event& event)
{
	return true;
}

bool PauseMenuComponent::functionPauseReturn(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->pause();
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, false); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...
	return true;
}

bool PauseMenuComponent::functionPauseReset(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(level);
	MotorCasaPaco::getInstance()->pause();
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, false); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...
	EventManager::getInstance()->EmitEvent("inicioNivel");
	return true;
}

bool PauseMenuComponent::functionPauseSettings(const CEGUI::EventArgs& e)
{
	//vainas de layouts
	layoutLayer++;
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, false); //Menú de Pausa Out
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(2, true); //Opciones Básicas In
	currentXTopButtons = 0;
	currentYTopButtons = tamBasicTop - 1;
	MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
	return true;
}

bool PauseMenuComponent::functionPauseMainMenu(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeScene(mainMenu);
	MotorCasaPaco::getInstance()->pause();
	EventManager::getInstance()->EmitEvent("finNivel");
	return true;
}

bool PauseMenuComponent::functionPauseExit(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->pause();
	MotorCasaPaco::getInstance()->exit();
	return true;
}

bool PauseMenuComponent::functionBasicGraphicOptions(const CEGUI::EventArgs& e)
{
	layoutLayer++;
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(2, false); //Menú de Pausa Out
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(3, true); //Opciones Básicas In
	currentXTopButtons = 0;
	currentYTopButtons = tamGraphicTop - 1;
	MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
	return true;
}

bool PauseMenuComponent::functionBasicBack(const CEGUI::EventArgs& e)
{
	layoutLayer--;
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, true); //Menú de Pausa In
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(2, false); //Opciones Básicas Out
	currenPos = 2;
	MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPause, positionsYPause[currenPos]);
	return true;
}

bool PauseMenuComponent::functionGraphicAdvancedOptions(const CEGUI::EventArgs& e)
{
	layoutLayer++;
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(3, false); //Menú de Pausa Out
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(4, true); //Opciones Básicas In
	currentXTopButtons = 0;
	currentYTopButtons = tamAdvancedTop - 1;
	MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsAdvanced[currentXTopButtons], positionsYAdvanced[currentYTopButtons]);
	return true;
}

bool PauseMenuComponent::functionGraphicApply(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeGraphicComponents();
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

bool PauseMenuComponent::functionGraphicRevert(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->revertGraphicChanges();
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);

	Event evt = Event("RESET_GRAPHIC_INFO");
	EventManager::getInstance()->EmitEvent(evt);

	return true;
}

bool PauseMenuComponent::functionGraphicBack(const CEGUI::EventArgs& e)
{
	layoutLayer--;
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(2, true); //Opciones Básicas In
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(3, false); //Menú de Graficos Out
	currenPos = 2;
	MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
	return true;
}

bool PauseMenuComponent::functionAdvancedBack(const CEGUI::EventArgs& e)
{
	layoutLayer--;
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(3, true); //Opciones Graficos In
	MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(4, false); //Menu Avanzado Out
	currenPos = 2;
	MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
	return true;
}

void PauseMenuComponent::update()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delayPause)
	{
		if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_START) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_ESCAPE))
		{
			MotorCasaPaco::getInstance()->pause();

			MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, true); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...

			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
	}
}

void PauseMenuComponent::pausedUpdate()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
	{
		switch (layoutLayer)
		{
			case 0: //Pause Menu
			{
				if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_START) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_ESCAPE))
				{
					if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delayPause)
					{
						MotorCasaPaco::getInstance()->pause();

						MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, false); //El orden de la UI es Ingame/Menu de Pausa/Opciones/Opciones Graficas/Opciones Avanzadas...
						
						layoutLayer = 0;

						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}

				if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
				{
					if (currenPos > 0)
						currenPos--;
					else
						currenPos = tamPause - 1;

					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPause, positionsYPause[currenPos]);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}

				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
				{
					if (currenPos < (tamPause - 1))
						currenPos++;
					else
						currenPos = 0;

					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPause, positionsYPause[currenPos]);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
			}
			break;

			case 1: //Basic Options
			{
				if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_B) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_ESCAPE))
				{
					layoutLayer--;
					MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, true); //Menú de Pausa Out
					MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(2, false); //Opciones Básicas In
					currenPos = 2;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPause, positionsYPause[currenPos]);
				}

				if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
				{
					if (basicTopDown == 2)
					{
						if (currentXTopButtons == 0)
						{
							currentXTopButtons++;
						}
						else
						{
							currentXTopButtons--;
						}

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
				{
					if (basicTopDown == 2)
					{
						if (currentXTopButtons == 0)
						{
							currentXTopButtons++;
						}
						else
						{
							currentXTopButtons--;
						}

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}

				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
				{
					if (basicTopDown == 2)
					{
						if (currentYTopButtons > 0) //Sigue en los botones de arriba
						{
							currentYTopButtons--;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
						else //Baja a los botones de abajo
						{
							basicTopDown--;
							currentYTopButtons = 0;
							currentXTopButtons = 0;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xBasicExtra, yBasicExtra);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
					}
					else if (basicTopDown == 1)
					{
						basicTopDown--;
						currentPosDownButtons = 1;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xBasicBack, yBasicBack);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (basicTopDown == 0)
					{
						basicTopDown = 2;
						currentYTopButtons = tamBasicTop - 1;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
				{
					if (basicTopDown == 2)
					{
						if (currentYTopButtons < tamBasicTop - 1) //Sigue en los botones de arriba
						{
							currentYTopButtons++;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
						else //Baja a los botones de abajo
						{
							basicTopDown = 0;
							currentPosDownButtons = 1;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xBasicBack, yBasicBack);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
					}
					else if (basicTopDown == 1)
					{
						basicTopDown++;
						currentYTopButtons = 0;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsBasic[currentXTopButtons], positionsYBasic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (basicTopDown == 0)
					{
						basicTopDown++;
						currentYTopButtons = 0;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xBasicExtra, yBasicExtra);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
			}
			break;

			case 2: //Graphic Options
			{
				if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_B) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_ESCAPE))
				{
					layoutLayer--;
					MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(1, true); //Menú de Pausa Out
					MotorCasaPaco::getInstance()->getGUI_Manager()->setLayoutVisible(2, false); //Opciones Básicas In
					currenPos = 2;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPause, positionsYPause[currenPos]);
				}

				if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
				{
					if (graphicTopDown == 2)
					{
						if (currentXTopButtons == 0)
						{
							currentXTopButtons++;
						}
						else
						{
							currentXTopButtons--;
						}

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (graphicTopDown == 0)
					{
						if (currentPosDownButtons == 0)
							currentPosDownButtons = tamGraphicDown - 1;
						else
							currentPosDownButtons--;

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsGraphic[currentPosDownButtons], yGraphicBot);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
				{
					if (graphicTopDown == 2)
					{
						if (currentXTopButtons == 0)
						{
							currentXTopButtons++;
						}
						else
						{
							currentXTopButtons--;
						}

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (graphicTopDown == 0)
					{
						if (currentPosDownButtons < 2)
							currentPosDownButtons++;
						else
							currentPosDownButtons = 0;

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsGraphic[currentPosDownButtons], yGraphicBot);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}

					//MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
					//currentTime = MotorCasaPaco::getInstance()->getTime();
				}

				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
				{
					if (graphicTopDown == 2)
					{
						if (currentYTopButtons > 0) //Sigue en los botones de arriba
						{
							currentYTopButtons--;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
						else //Baja a los botones de abajo
						{
							graphicTopDown--;
							currentYTopButtons = 0;
							currentXTopButtons = 0;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xExtraGraphic, yExtraGraphic); //Extra Button
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
					}
					else if (graphicTopDown == 1)
					{
						graphicTopDown--;
						currentPosDownButtons = 1;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsGraphic[currentPosDownButtons], yGraphicBot);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (graphicTopDown == 0)
					{
						graphicTopDown = 2;
						currentYTopButtons = tamGraphicTop - 1;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
				{
					if (graphicTopDown == 2)
					{
						if (currentYTopButtons < tamGraphicTop - 1) //Sigue en los botones de arriba
						{
							currentYTopButtons++;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
						else //Baja a los botones de abajo
						{
							graphicTopDown = 0;
							currentPosDownButtons = 1;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsGraphic[currentPosDownButtons], yGraphicBot);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
					}
					else if (graphicTopDown == 1)
					{
						graphicTopDown++;
						currentYTopButtons = 0;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsGraphic[currentXTopButtons], positionsYGraphic[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (graphicTopDown == 0)
					{
						graphicTopDown++;
						currentYTopButtons = 0;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xExtraGraphic, yExtraGraphic); //Extra Button
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
			}
			break;

			case 3: //Advanced Graphic Options
			{
				if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
				{
					if (advancedTopDown == 1)
					{
						if (currentXTopButtons == 0)
						{
							currentXTopButtons++;
						}
						else
						{
							currentXTopButtons--;
						}

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsAdvanced[currentXTopButtons], positionsYAdvanced[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (advancedTopDown == 0)
					{
						if (currentPosDownButtons == 0)
							currentPosDownButtons = tamAdvancedTop - 1;
						else
							currentPosDownButtons--;

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsAdvanced[currentPosDownButtons], yAdvancedBot);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
				{
					if (advancedTopDown == 1)
					{
						if (currentXTopButtons == 0)
						{
							currentXTopButtons++;
						}
						else
						{
							currentXTopButtons--;
						}

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsAdvanced[currentXTopButtons], positionsYAdvanced[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
					else if (advancedTopDown == 0)
					{
						if (currentPosDownButtons < 2)
							currentPosDownButtons++;
						else
							currentPosDownButtons = 0;

						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsAdvanced[currentPosDownButtons], yAdvancedBot);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}

					//MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
					//currentTime = MotorCasaPaco::getInstance()->getTime();
				}

				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_S) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_DOWN))
				{
					if (advancedTopDown == 1)
					{
						if (currentYTopButtons > 0) //Sigue en los botones de arriba
						{
							currentYTopButtons--;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsAdvanced[currentXTopButtons], positionsYAdvanced[currentYTopButtons]);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
						else //Baja a los botones de abajo
						{
							advancedTopDown = 0;
							currentYTopButtons = 0;
							currentXTopButtons = 0;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsAdvanced[currentPosDownButtons], yAdvancedBot);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
					}
					else if (advancedTopDown == 0)
					{
						advancedTopDown = 1;
						currentYTopButtons = tamAdvancedTop - 1;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsAdvanced[currentXTopButtons], positionsYAdvanced[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_W) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_UP))
				{
					if (advancedTopDown == 1)
					{
						if (currentYTopButtons < tamAdvancedTop - 1) //Sigue en los botones de arriba
						{
							currentYTopButtons++;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsAdvanced[currentXTopButtons], positionsYAdvanced[currentYTopButtons]);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
						else //Baja a los botones de abajo
						{
							advancedTopDown = 0;
							currentPosDownButtons = 1;
							MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXBotButtonsAdvanced[currentPosDownButtons], yAdvancedBot);
							currentTime = MotorCasaPaco::getInstance()->getTime();
						}
					}
					else if (advancedTopDown == 0)
					{
						advancedTopDown++;
						currentYTopButtons = 0;
						currentXTopButtons = 0;
						MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtonsAdvanced[currentXTopButtons], positionsYAdvanced[currentYTopButtons]);
						currentTime = MotorCasaPaco::getInstance()->getTime();
					}
				}
			}
			break;
		}

		if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE))
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
		else
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
		}
	}
}

void PauseMenuComponent::init(json& j)
{
	if (!j["delayPause"].is_null() && !j["delay"].is_null() && !j["buttons"].is_null() && j["buttons"].is_array())
	{
		/////////////////////////////////////////////////////////
		//Pause Menu Stuff

		std::vector<std::string> vec = j["buttons"];

		int count = 0;
		for (std::string name : vec) {

			if (count == 0)
				xPause = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			
			float y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

			positionsYPause.push_back(y);

			//Asignacion de funciones

			switch (count)
			{
			case 0:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionPauseReturn, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 1:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionPauseReset, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 2:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionPauseSettings, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 3:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionPauseMainMenu, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 4:
			{
				auto helperFunction = std::bind(&PauseMenuComponent::functionPauseExit, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			}

			count++;
		}

		tamPause = count;

		//////////////////////////////////////////////////////////////
		//Basic Options Stuff

		std::vector<std::string> vec2 = j["basicOptionButtons"];

		count = 0;

		for (std::string name : vec2)
		{
			if (count < 2)
			{
				float x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
				positionsXTopButtonsBasic.push_back(x);
			}

			if (count % 2 == 0)
			{
				float y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

				positionsYBasic.push_back(y);
			}

			//Asignacion de funciones

			switch (count)
			{
			case 0:
			{
				//auto helperFunction = std::bind(&PauseMenuComponent::functionReturn, this, std::placeholders::_1);
				//GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction);
			}
			break;
			case 1:
			{

			}
			break;
			case 2:
			{

			}
			break;
			case 3:
			{

			}
			break;
			case 4:
			{

			}
			break;
			case 5:
			{

			}
			break;
			case 6:
			{

			}
			break;
			case 7:
			{

			}
			break;
			case 8:
			{

			}
			break;
			case 9:
			{

			}
			break;
			}
			
			count++;
		}

		tamBasicTop = count / 2;

		std::string interm = j["basicExtraButton"];
		yBasicExtra = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(interm).getCenterPointYAbsolute();
		xBasicExtra = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(interm).getCenterPointYAbsolute();

		//Assign function

		auto helperFunction = std::bind(&PauseMenuComponent::functionBasicGraphicOptions, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(interm), helperFunction);

		std::string back = j["basicBackButton"];
		yBasicBack = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(back).getCenterPointYAbsolute();
		xBasicBack = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(back).getCenterPointYAbsolute();

		//Assign function

		auto helperFunction1 = std::bind(&PauseMenuComponent::functionBasicBack, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(back), helperFunction1);

		//////////////////////////////////////////////////////////////
		//Graphic Options Stuff

		std::vector<std::string> vec3 = j["graphicOptionDownButtons"];

		float y;
		count = 0;

		for (std::string name : vec3)
		{
			float x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			
			if (count == 0)
				y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

			positionsXBotButtonsGraphic.push_back(x);

			//Asignacion de funciones

			switch (count)
			{
			case 0:
			{
				auto helperFunctionGraphicBot = std::bind(&PauseMenuComponent::functionGraphicApply, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(back), helperFunctionGraphicBot);
			}
			break;
			case 1:
			{
				auto helperFunctionGraphicBot = std::bind(&PauseMenuComponent::functionGraphicRevert, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(back), helperFunctionGraphicBot);
			}
			break;
			case 2:
			{
				auto helperFunctionGraphicBot = std::bind(&PauseMenuComponent::functionGraphicBack, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunctionGraphicBot);
			}
			break;
			}

			count++;
		}

		yGraphicBot = y;

		tamGraphicDown = count;

		std::vector<std::string> vec4 = j["graphicOptionTopButtons"];

		count = 0;

		for (std::string name : vec4) //Faltan funciones de los botones
		{
			if (count < 2)
			{
				float x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
				positionsXTopButtonsGraphic.push_back(x);
			}

			if (count % 2 == 0)
			{
				y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

				positionsYGraphic.push_back(y);
			}

			//Asignacion de funciones

			switch (count)
			{
			case 0:
			{

			}
			break;
			case 1:
			{

			}
			break;
			case 2:
			{

			}
			break;
			case 3:
			{

			}
			break;
			case 4:
			{

			}
			break;
			case 5:
			{

			}
			break;
			case 6:
			{

			}
			break;
			case 7:
			{

			}
			break;
			case 8:
			{

			}
			break;
			case 9:
			{

			}
			break;
			}

			count++;
		}

		tamGraphicTop = count / 2;
		
		std::string name = j["graphicOptionExtraButton"];
		xExtraGraphic = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
		yExtraGraphic = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

		auto helperFunction2 = std::bind(&PauseMenuComponent::functionGraphicAdvancedOptions, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunction2);

		//////////////////////////////////////////////////////////////
		//Advanced Graphic Options Stuff

		std::vector<std::string> vec5 = j["advancedGraphicOptionDownButtons"];

		count = 0;

		for (std::string name : vec5)
		{
			float x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();

			if (count == 0)
				y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

			positionsXBotButtonsAdvanced.push_back(x);

			//Asignacion de funciones

			switch (count)
			{
			case 0:
			{
				auto helperFunctionAdvancedBot = std::bind(&PauseMenuComponent::functionAdvancedBack, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunctionAdvancedBot);
			}
			break;
			case 1:
			{
				auto helperFunctionAdvancedBot = std::bind(&PauseMenuComponent::functionAdvancedBack, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunctionAdvancedBot);
			}
			break;
			case 2:
			{
				auto helperFunctionAdvancedBot = std::bind(&PauseMenuComponent::functionAdvancedBack, this, std::placeholders::_1);
				GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(name), helperFunctionAdvancedBot);
			}
			break;
			}

			count++;
		}

		yAdvancedBot = y;

		tamAdvancedDown = count;

		std::vector<std::string> vec6 = j["advancedGraphicOptionTopButtons"];

		count = 0;

		for (std::string name : vec6) //Faltan funciones de los botones
		{
			if (count < 2)
			{
				float x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
				positionsXTopButtonsAdvanced.push_back(x);
			}

			if (count % 2 == 0)
			{
				y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

				positionsYAdvanced.push_back(y);
			}

			//Asignacion de funciones

			switch (count)
			{
			case 0:
			{

			}
			break;
			case 1:
			{

			}
			break;
			case 2:
			{

			}
			break;
			case 3:
			{

			}
			break;
			case 4:
			{

			}
			break;
			case 5:
			{

			}
			break;
			case 6:
			{

			}
			break;
			case 7:
			{

			}
			break;
			case 8:
			{

			}
			break;
			case 9:
			{

			}
			break;
			case 10:
			{

			}
			break;
			case 11:
			{

			}
			break;
			case 12:
			{

			}
			break;
			case 13:
			{

			}
			break;
			}

			count++;
		}

		tamAdvancedTop = count / 2;

		//////////////////////////////////////////////////////////////

		std::string interm2 = j["Level"];
		level = interm2;

		std::string interm3 = j["MainMenu"];
		mainMenu = interm3;

		delay = j["delay"];
		delayPause = j["delayPause"];

		currenPos = 0;
		layoutLayer = 0;
		currentTime = MotorCasaPaco::getInstance()->getTime();

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPause, positionsYPause[currenPos]);
	}
}

#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_front(1);
	pros::Motor right_front(2);
	pros::Motor left_back(3);
	pros::Motor right_back(4);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int vertical = master.get_analog(ANALOG_LEFT_Y);
		int horizontal = master.get_analog(ANALOG_LEFT_X);
		int turn = master.get_analog(ANALOG_RIGHT_X);

		#define VMH (vertical-horizontal)
		#define VPH (vertical+horizontal)
		left_front.move(VPH+turn);
		right_front.move(VMH-turn);
		right_back.move(VPH-turn);
		left_back.move(VMH+turn);
		
		pros::delay(20);
	}
}

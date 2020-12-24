#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Opengl.hpp>
#include <fstream>
#include <Windows.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <cmath>

class Watches
{
public:
	Watches();

	void RunWatches();

private:
	
	std::unordered_map<std::string,sf::RectangleShape> arrows;
	std::vector<sf::Text> digits;
	sf::Font digits_font;

	void InitArrows();
	
	void UpdateArrows();

	
	
	void DrawArrows(sf::RenderWindow& w);
	
	void DrawDigits(sf::RenderWindow& w);

	void LoadFont();

	void InitDigits();

	void SetDigitPosition(sf::Text& t, size_t current_angle);

	

	const size_t window_height = 600;
	const size_t window_width = 800;

	const float window_center_x = window_width / 2;
	const float window_center_y = window_height / 2;

	const float hours_angle = 360 / 12;
	const float minutes_angle = 360 / 60;
	const float seconds_angle = 360 / 60;
	const float milliseconds_angle = 0.36666f; // this should have been 360 / 1000 but it doesn't work correctly

	const size_t clockface_radius = 260;

	bool font_loaded = false; 

	const float sfml_angle_correction = 90;   //SFML 0 degrees point is not at 12 o'clock, but at 3

	const float pi = 3.141592653;

	const float stl_angle_correction = 3*pi / 2; // std::cosf and std::sinf expect values in radians to work correctly

	const float hour_arrow_angle_movement = 360 / 24;
	
};


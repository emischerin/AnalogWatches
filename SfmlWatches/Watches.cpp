#include "Watches.h"

Watches::Watches()
{
	this->InitArrows();
	this->LoadFont();
	
	if (font_loaded) this->InitDigits();
}

void Watches::InitArrows()
{

	

	sf::RectangleShape seconds_arrow(sf::Vector2f(250, 5));
	sf::RectangleShape minute_arrow(sf::Vector2f(200, 5));
	sf::RectangleShape hour_arrow(sf::Vector2f(150, 5));
	sf::RectangleShape milliseconds_arrow(sf::Vector2f(100, 5));


	seconds_arrow.setFillColor(sf::Color::Green);
	minute_arrow.setFillColor(sf::Color::White);
	hour_arrow.setFillColor(sf::Color::Cyan); 
	milliseconds_arrow.setFillColor(sf::Color::Red);


	seconds_arrow.setPosition(sf::Vector2f(window_center_x, window_center_y));
	minute_arrow.setPosition(sf::Vector2f(window_center_x, window_center_y));
	hour_arrow.setPosition(sf::Vector2f(window_center_x, window_center_y));
	milliseconds_arrow.setPosition(sf::Vector2f(window_center_x, window_center_y));

	


	arrows["hours"] = hour_arrow;
	arrows["minutes"] = minute_arrow;
	arrows["seconds"] = seconds_arrow;
	arrows["milliseconds"] = milliseconds_arrow;
	
}

void Watches::UpdateArrows()
{
	SYSTEMTIME sys_time;

	GetLocalTime(&sys_time);


	
	//arrows["hours"].setRotation((sys_time.wHour * hours_angle) - sfml_angle_correction);
	arrows["hours"].setRotation((sys_time.wHour * hours_angle) - sfml_angle_correction + 
		hour_arrow_angle_movement);
	

	
	arrows["minutes"].setRotation((sys_time.wMinute * minutes_angle) - sfml_angle_correction);
	arrows["seconds"].setRotation((sys_time.wSecond * seconds_angle) - sfml_angle_correction);
	arrows["milliseconds"].setRotation((sys_time.wMilliseconds * milliseconds_angle) - sfml_angle_correction);




}

void Watches::LoadFont()
{
		
	if (!digits_font.loadFromFile("fnt.f")) {
		throw("Font not found");
	}
	else {
		font_loaded = true;
	}
}

void Watches::RunWatches()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Watches");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
	
		
		
		window.clear();
		UpdateArrows();
		DrawDigits(window);
		DrawArrows(window);
		window.display();

	}
}

void Watches::DrawArrows(sf::RenderWindow& w)
{
	
	w.draw(arrows["hours"]);
	w.draw(arrows["minutes"]);
	w.draw(arrows["seconds"]);
	w.draw(arrows["milliseconds"]);
}

inline void Watches::DrawDigits(sf::RenderWindow& w)
{
	
	for (sf::Text t : digits) {
		w.draw(t);
	}
}

void Watches::InitDigits()
{
	sf::RectangleShape position(sf::Vector2f(260, 5));
	sf::Text t;
	
	


	size_t clockface_digits = 1;
	for (size_t i(hours_angle); i != 360; i += hours_angle) {
		t.setFont(this->digits_font);
		t.setString(std::to_string(clockface_digits));
		t.setCharacterSize(25);
		t.setFillColor(sf::Color::White);
		t.setStyle(sf::Text::Bold);
		SetDigitPosition(t,i);
		digits.push_back(t);

		clockface_digits++;

	}

	//We have to write 12 o clock separately

	t.setFont(this->digits_font);
	t.setString(std::to_string(12));
	t.setCharacterSize(25);
	t.setFillColor(sf::Color::White);
	t.setStyle(sf::Text::Bold);
	SetDigitPosition(t, 360);
	digits.push_back(t);

}



inline void Watches::SetDigitPosition(sf::Text& t,size_t current_angle)
{
	float cosx_rad = std::cosf(stl_angle_correction + (current_angle * pi) / 180);
	float siny_rad = std::sinf(stl_angle_correction + (current_angle * pi) / 180);

	float digit_x = (clockface_radius * cosx_rad);
	float digit_y = (clockface_radius * siny_rad );


	/*Changing coordinate space from usual abstract math to Windows*/
	digit_x = (digit_x + window_center_x);
	digit_y = std::abs(digit_y + window_center_y);

	t.setPosition(digit_x, digit_y);
	
	
}
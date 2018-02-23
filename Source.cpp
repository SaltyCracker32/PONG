#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>
#include <stdio.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<iostream>
using namespace std;

bool collision (int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
const float FPS = 60;
const int SCREEN_W = 1900;
const int SCREEN_H = 1000;
const int BOUNCER_SIZE = 32;
const int BOUNCER_HEIGHT = 180;
const int BOUNCER_WIDTH = 32;
const int BOUNCER2_SIZE = 32;
const int BOUNCER2_HEIGHT = 180;
const int BOUNCER2_WIDTH = 32;
const int BOUNCER3_SIZE = 10;

int Bouncerscore;
int Bouncer2score;

enum MYKEYS {
	KEY_UP, KEY_DOWN
};

enum MYKEYS2 {
	KEY_W, KEY_S
};

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	ALLEGRO_BITMAP *bouncer2 = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_BITMAP *bouncer3 = NULL;
	ALLEGRO_SAMPLE *sample = NULL;
	ALLEGRO_SAMPLE *sample2 = NULL;
	ALLEGRO_SAMPLE *sample3 = NULL;
	
	float bouncer_x = 1870;
	float bouncer_y = 350;
	float bouncer2_x = 1;
	float bouncer2_y = 350;
	float bouncer3_x = 300;
	float bouncer3_y = 200;

	float bouncer3_dx = -5.0, bouncer3_dy = 2.0;


	bool key1[2] = { false, false };//remember to change the key number for multiple people to play
	bool key2[2] = { false, false };
	bool redraw = true;
	bool doexit = false;

	al_init();

	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	timer = al_create_timer(1.0 / FPS);
	al_reserve_samples(3);

	font = al_load_ttf_font("cubic.ttf", 20, 0);
	sample = al_load_sample("Beep2.wav");
	sample2 = al_load_sample("Beep3.wav");
	sample3 = al_load_sample("SiliconTransmitter.wav");


	display = al_create_display(SCREEN_W, SCREEN_H);
	bouncer = al_create_bitmap(32, 150);
	bouncer2 = al_create_bitmap(32, 150);
	bouncer3 = al_create_bitmap(10, 10);

	al_set_target_bitmap(bouncer);

	al_clear_to_color(al_map_rgb(250, 250, 250));

	al_play_sample(sample3, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	al_set_target_bitmap(al_get_backbuffer(display));


	al_set_target_bitmap(bouncer2);
	al_clear_to_color(al_map_rgb(250, 250, 250));

	al_set_target_bitmap(bouncer3);
	al_clear_to_color(al_map_rgb(250, 250, 250));

	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key2[KEY_W] && bouncer2_y >= 4.0) {
				bouncer2_y -= 7.0;
			}

			if (key2[KEY_S] && bouncer2_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
				bouncer2_y += 7.0;
			}

			if (key1[KEY_UP] && bouncer_y >= 4.0) {
				bouncer_y -= 7.0;
			}

			if (key1[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
				bouncer_y += 7.0;
			}

			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key1[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key1[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_W:
				key2[KEY_W] = true;
				break;

			case ALLEGRO_KEY_S:
				key2[KEY_S] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key1[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key1[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_W:
				key2[KEY_W] = false;
				break;

			case ALLEGRO_KEY_S:
				key2[KEY_S] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			}
		}

		if (bouncer3_x <= 0) {
			Bouncerscore++;
			al_play_sample(sample2, 1.0, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
			bouncer3_dx = -bouncer3_dx;
			

		}

		if (bouncer3_x >= 1860) {
			Bouncer2score++;
			al_play_sample(sample2, 1.0, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
			bouncer3_dx = -bouncer3_dx;
			


		}

		if (bouncer3_y < 0 || bouncer3_y > 1000) {
			bouncer3_dy = -bouncer3_dy;

		}

		bouncer3_x += bouncer3_dx;
		bouncer3_y += bouncer3_dy;

		if (collision(bouncer_x, bouncer_y, BOUNCER_WIDTH, BOUNCER_HEIGHT, bouncer3_x, bouncer3_y, 22, 32) == true) {
			al_play_sample(sample, 1.0, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
			bouncer3_dx = -bouncer3_dx;

		}

		if (collision(bouncer2_x, bouncer2_y, BOUNCER2_WIDTH, BOUNCER2_HEIGHT, bouncer3_x, bouncer3_y, 32, 32) == true) {
			al_play_sample(sample, 1.0, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
			bouncer3_dx = -bouncer3_dx;

		}

		if (bouncer3_x < 0 || bouncer3_x > SCREEN_W - BOUNCER_SIZE) {
			bouncer3_dx = -bouncer3_dx;
		}

		if (bouncer3_y < 0 || bouncer3_y > SCREEN_H - BOUNCER_SIZE) {
			bouncer3_dy = -bouncer3_dy;
		}


		bouncer3_x += bouncer3_dx;
		bouncer3_y += bouncer3_dy;
		redraw = true;
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
			al_draw_bitmap(bouncer2, bouncer2_x, bouncer2_y, 0);
			al_draw_bitmap(bouncer3, bouncer3_x, bouncer3_y, 0);



			al_draw_textf(font, al_map_rgb(250, 250, 250), 550, 50, ALLEGRO_ALIGN_CENTER, "%d", Bouncerscore);
			al_draw_textf(font, al_map_rgb(250, 250, 250), 1300, 50, ALLEGRO_ALIGN_CENTER, "%d", Bouncer2score);


			al_flip_display();

		}
	}//end of game loop
	al_destroy_bitmap(bouncer);
	al_destroy_bitmap(bouncer2);
	al_destroy_bitmap(bouncer3);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;

}//end of main

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {

	if ((x1 + w2) > x2 && x1 <(x2 + w2) && (y1 + h1) > y2 && y1 < (y2 + h2)) {
		return true;

	}

	else {
		return false;


	}




}

#include "storage.h"
#include "Preferences.h"
Preferences preferences;

Storage::Storage() {}

Storage storage;


void Storage::get_or_set_id(char * buffer) {
	preferences.begin("id");
    if ( preferences.isKey("deviceID") ) {
        strcpy( buffer, preferences.getString("deviceID").c_str() );
        Serial.print("\tdeviceID exists: ");
        Serial.println(buffer);
    } else {
        char code_holder[9];
        _create_code(code_holder);
        strcpy( buffer, code_holder );
        preferences.putString("deviceID", (const char *) buffer);
        Serial.print("\t\tno 'deviceID' key existed.  id created: ");
        Serial.println(buffer);
    }
    preferences.end();
}


void Storage::clear_id() {
    preferences.begin("id");
    preferences.clear();
    preferences.end();
}


void Storage::_create_code(char * buffer) {
	const char * character_options = "abcdefghijklmnopqrstuvwxyz0123456789";
	for (int i = 0; i<8; i++) {
		int selection = random(36);
		buffer[i] = character_options[selection];
	}
	buffer[8] = 0;
}



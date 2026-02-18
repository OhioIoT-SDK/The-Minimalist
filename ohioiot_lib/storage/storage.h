#pragma once


class Storage {

    public:

        Storage();

        void get_or_set_id(char * buffer);
        void clear_id();

    private:

        void _create_code(char * buffer);

};

extern Storage storage;



#ifndef CONSTANTS
#define CONSTANTS


const uint PLAYER_AMOUNT = 5;
enum PLAYER_NUM
{
    DRACULA_NUM = 0,
    LORD_NUM = 1,
    DOCTOR_NUM = 2,
    HELSING_NUM = 3,
    MINA_NUM = 4
};

const QString DRACULA_NAME = "Dracula";
const QString DOCTOR_NAME = "Dr. Steward";
const QString LORD_NAME = "Lord Godalming";
const QString HELSING_NAME = "Van Helsing";
const QString MINA_NAME = "Mina Harper";

const uint DRACULA_MAX_HEALTH = 15;
const uint LORD_MAX_HEALTH = 12;
const uint DOCTOR_MAX_HEALTH = 10;
const uint HELSING_MAX_HEALTH = 8;
const uint MINA_MAX_HEALTH = 8;

const uint CASTLE_DRACULA_NUM = 24;
const uint HOSPITAL_NUM = 60;

const int DAY_LENTH = 6;
const int HUNTER_SCORE_PLACES_NUM = 7;
const int DRACULA_SCORE_PLACES_NUM = 7;

const int DRACULA_MAX_SCORE = 6;
const int HUNTER_MAX_SCORE = 6;

const uint TRACK_SIZE = 6;
const uint CATACOMBS_SIZE = 3;

#endif // CONSTANTS


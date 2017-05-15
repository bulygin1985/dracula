#ifndef CONSTANTS
#define CONSTANTS

#include <QString>

enum class ActionType
{
    LOCATION = 0,
    POWER = 1,
    TRAIN_DICE = 2,
    HUNTER_DICE = 3,
    DRACULA_DICE = 4,
    EVENT_FROM_HAND = 5,
    ITEM_FROM_HAND = 6,
    EVENT_DECK = 7,
    ITEM_DECK = 8,
    ENCOUNTER_FROM_HAND = 9,
    DISCARD_EVENT = 10,
    DISCARD_ITEM = 11,
    CHOOSE_PLAYER = 12
};

const int PLAYER_AMOUNT = 5;
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

const int DRACULA_CASTLE_NUM = 24;

const int LOCATION_NUMBER = 71;

const int CITIES_NUMBER = 61;

const int HOSPITAL_NUM = 60;

const int DAY_LENTH = 6;
const int HUNTER_SCORE_PLACES_NUM = 7;
const int DRACULA_SCORE_PLACES_NUM = 7;

const int DRACULA_MAX_SCORE = 6;
const int HUNTER_MAX_SCORE = 6;

const uint TRACK_SIZE = 6;
const uint CATACOMBS_SIZE = 3;

#endif // CONSTANTS


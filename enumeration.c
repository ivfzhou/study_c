#include "enumeration.h"

enum week test_enum() {
    enum inner_week {
        INNER_MON,
        INNER_TUES,
        INNER_WED,
        INNER_THURS,
        INNER_FRI,
        INNER_SAT,
        INNER_SUN
    };
    enum inner_week w = INNER_TUES;
    return (enum week) w;
}

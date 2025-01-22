// 枚举的声明
enum week {
    MON, /* 值为0 */
    TUES,
    WED,
    THURS,
    FRI,
    SAT,
    SUN
};

enum level {
    LOW = 100,
    MEDIUM = 500,
    HIGH = 2000,
    HIGHEST /* 值为2001 */
};

static enum week enumeration() {
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
    return (enum week)w;
}

void test_enumeration() {
    enumeration();
}

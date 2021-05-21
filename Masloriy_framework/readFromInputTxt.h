#pragma once

void txt(bool reopenInput, bool reopenOutput, bool turnOffSync);

struct prerun {
    prerun(bool reopenInput, bool reopenOutput, bool turnOffSync = false) {
        txt(reopenInput, reopenOutput, turnOffSync);
    }
};

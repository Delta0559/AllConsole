#pragma once

#include "../Utilities/SubActionManager.h"

template<typename T1, typename T2>
constexpr bool STATE(T1 str, T2  state) { return (SubActionManager::if_(str, state)); }

template<typename T>
constexpr auto _Print(T args) { qDebug() << args; }

#define BACK_AND_QUIT_CHECK(Str)        if (STATE(Str, SubActionManager::Statement::Back)) { \
                                            return SubActionManager::Action::Back; \
                                        } \
                                        if (STATE(Str, SubActionManager::Statement::Quit)) { \
                                            return SubActionManager::Action::Quit; \
                                        }
#define BACK_CHECK(Str)                 if (STATE(Str, SubActionManager::Statement::Back)) { \
                                            return SubActionManager::Action::Back; \
                                        }
#define QUIT_CHECK(Str)                 if (STATE(Str, SubActionManager::Statement::Quit)) { \
                                            return SubActionManager::Action::Quit; \
                                        }

constexpr auto expINFO = "info";
constexpr auto expOPTIONS = "!options";

constexpr auto expCAESAR = "Caesar";
constexpr auto expPOM = "POM";
constexpr auto expPENDU = "Pendu";

constexpr auto expQUIT = "quit";
constexpr auto expBACK = "back";
constexpr auto expCLEAN = "!clean";

constexpr auto expYES = "Oui";
constexpr auto expNO = "Non";

constexpr auto expINPUT = "input";
constexpr auto expCANCEL = "cancel";
constexpr auto expSHOW = "show";
constexpr auto expREMOVE = "remove";
constexpr auto expPLAY = "play";

constexpr auto expWORD = "word";
constexpr auto expSENTENCE = "sentence";

constexpr auto expALL = "all";

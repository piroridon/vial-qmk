// Copyright 2025 piroridon (@piroridon)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define PERMISSIVE_HOLD

#define MOUSEKEY_INERTIA
#define MOUSEKEY_DELAY 125
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 32
#define MOUSEKEY_TIME_TO_MAX 32
#define MOUSEKEY_FRICTION 32
#define MOUSEKEY_MOVE_DELTA 1

#define ENCODER_DEFAULT_POS 0x3

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

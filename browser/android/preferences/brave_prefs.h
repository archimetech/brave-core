// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BRAVE_BROWSER_ANDROID_PREFERENCES_BRAVE_PREFS_H_
#define BRAVE_BROWSER_ANDROID_PREFERENCES_BRAVE_PREFS_H_

#include <cstddef>

#include "build/build_config.h"
#include "components/ntp_sponsored_images/common/pref_names.h"

// A preference exposed to Java.
// A Java counterpart will be generated for this enum.
// GENERATED_JAVA_ENUM_PACKAGE: org.chromium.chrome.browser.preferences
enum BravePref {
  NTP_SHOW_BRANDED_BACKGROUND_IMAGE,
  NTP_SHOW_BACKGROUND_IMAGE,
  // BRAVE_PREF_NUM_PREFS must be the last entry.
  BRAVE_PREF_NUM_PREFS
};

// The indices must match value of Pref.
const char* const kBravePrefsExposedToJava[] = {
    ntp_sponsored_images::prefs::kNewTabPageShowBrandedBackgroundImage[],
    ntp_sponsored_images::prefs::kNewTabPageShowBackgroundImage[],
};

#endif  // BRAVE_BROWSER_ANDROID_PREFERENCES_BRAVE_PREFS_H_

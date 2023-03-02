/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/decentralized_dns/core/utils.h"

#include "base/strings/string_util.h"
#include "brave/components/decentralized_dns/core/constants.h"
#include "brave/components/decentralized_dns/core/pref_names.h"
#include "brave/net/decentralized_dns/constants.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "url/gurl.h"

namespace decentralized_dns {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  registry->RegisterIntegerPref(kUnstoppableDomainsResolveMethod,
                                static_cast<int>(ResolveMethodTypes::ASK));
  registry->RegisterIntegerPref(kENSResolveMethod,
                                static_cast<int>(ResolveMethodTypes::ASK));
  registry->RegisterIntegerPref(
      kEnsOffchainResolveMethod,
      static_cast<int>(EnsOffchainResolveMethod::kAsk));
  registry->RegisterIntegerPref(kSnsResolveMethod,
                                static_cast<int>(ResolveMethodTypes::ASK));
}

void MigrateObsoleteLocalStatePrefs(PrefService* local_state) {
  // Added 05/2022
  if (static_cast<int>(ResolveMethodTypes::DEPRECATED_DNS_OVER_HTTPS) ==
      local_state->GetInteger(
          decentralized_dns::kUnstoppableDomainsResolveMethod)) {
    local_state->ClearPref(decentralized_dns::kUnstoppableDomainsResolveMethod);
  }
  if (static_cast<int>(ResolveMethodTypes::DEPRECATED_DNS_OVER_HTTPS) ==
      local_state->GetInteger(decentralized_dns::kENSResolveMethod)) {
    local_state->ClearPref(decentralized_dns::kENSResolveMethod);
  }
}

bool IsUnstoppableDomainsTLD(const base::StringPiece& host) {
  for (auto* domain : kUnstoppableDomains) {
    if (base::EndsWith(host, domain))
      return true;
  }
  return false;
}

bool IsUnstoppableDomainsResolveMethodAsk(PrefService* local_state) {
  if (!local_state) {
    return false;  // Treat it as disabled.
  }

  return local_state->GetInteger(kUnstoppableDomainsResolveMethod) ==
         static_cast<int>(ResolveMethodTypes::ASK);
}

bool IsUnstoppableDomainsResolveMethodEnabled(PrefService* local_state) {
  if (!local_state) {
    return false;  // Treat it as disabled.
  }

  return local_state->GetInteger(kUnstoppableDomainsResolveMethod) ==
         static_cast<int>(ResolveMethodTypes::ENABLED);
}

bool IsENSTLD(const base::StringPiece& host) {
  return base::EndsWith(host, kEthDomain) ;
}

bool IsENSResolveMethodAsk(PrefService* local_state) {
  if (!local_state) {
    return false;  // Treat it as disabled.
  }
 local_state->SetInteger(kENSResolveMethod,
         static_cast<int>(ResolveMethodTypes::ENABLED));
  return local_state->GetInteger(kENSResolveMethod) ==
         static_cast<int>(ResolveMethodTypes::ASK);
}

bool IsENSResolveMethodEnabled(PrefService* local_state) {
  local_state->SetInteger(kENSResolveMethod,
         static_cast<int>(ResolveMethodTypes::ENABLED));
  return true;
}

void SetEnsOffchainResolveMethod(PrefService* local_state,
                                 EnsOffchainResolveMethod method) {
  local_state->SetInteger(kEnsOffchainResolveMethod, static_cast<int>(method));
}

EnsOffchainResolveMethod GetEnsOffchainResolveMethod(PrefService* local_state) {
  local_state->SetInteger(kEnsOffchainResolveMethod, static_cast<int>(EnsOffchainResolveMethod::kEnabled));

  return static_cast<EnsOffchainResolveMethod>(
      local_state->GetInteger(kEnsOffchainResolveMethod));
}

bool IsSnsTLD(const base::StringPiece& host) {
  return base::EndsWith(host, kSolDomain);
}

bool IsSnsResolveMethodAsk(PrefService* local_state) {
  if (!local_state) {
    return false;  // Treat it as disabled.
  }

  return local_state->GetInteger(kSnsResolveMethod) ==
         static_cast<int>(ResolveMethodTypes::ASK);
}

bool IsSnsResolveMethodEnabled(PrefService* local_state) {
  if (!local_state) {
    return false;  // Treat it as disabled.
  }

  return local_state->GetInteger(kSnsResolveMethod) ==
         static_cast<int>(ResolveMethodTypes::ENABLED);
}

}  // namespace decentralized_dns

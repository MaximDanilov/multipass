/*
 * Copyright (C) 2019 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MULTIPASS_COMMON_IMAGE_HOST_H_
#define MULTIPASS_COMMON_IMAGE_HOST_H_

#include "multipass/vm_image_host.h"

#include <chrono>

namespace multipass
{

class CommonVMImageHost : public VMImageHost
{
public:
    CommonVMImageHost(std::chrono::seconds manifest_time_to_live);
    void for_each_entry_do(const Action& action) final;
    VMImageInfo info_for_full_hash(const std::string& full_hash) final;

protected:
    void update_manifests();

    virtual void for_each_entry_do_impl(const Action& action) = 0;
    virtual VMImageInfo info_for_full_hash_impl(const std::string& full_hash) = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;
    virtual void fetch_manifests() = 0;

private:
    std::chrono::seconds manifest_time_to_live;
    std::chrono::steady_clock::time_point last_update;

};

}


#endif /* MULTIPASS_COMMON_IMAGE_HOST_H_ */

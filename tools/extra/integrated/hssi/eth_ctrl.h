// Copyright(c) 2017-2018, Intel Corporation
//
// Redistribution  and  use  in source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of  source code  must retain the  above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name  of Intel Corporation  nor the names of its contributors
//   may be used to  endorse or promote  products derived  from this  software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO,  THE
// IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT  SHALL THE COPYRIGHT OWNER  OR CONTRIBUTORS BE
// LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR
// CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT LIMITED  TO,  PROCUREMENT  OF
// SUBSTITUTE GOODS OR SERVICES;  LOSS OF USE,  DATA, OR PROFITS;  OR BUSINESS
// INTERRUPTION)  HOWEVER CAUSED  AND ON ANY THEORY  OF LIABILITY,  WHETHER IN
// CONTRACT,  STRICT LIABILITY,  OR TORT  (INCLUDING NEGLIGENCE  OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,  EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
#pragma once
#include <cstdint>
#include "przone.h"

namespace intel
{
namespace fpga
{
namespace hssi
{


class eth_ctrl
{
public:
    typedef std::shared_ptr<eth_ctrl> ptr_t;

    enum
    {
        eth_instance_bit = 12
    };

    enum class eth_traff_cmd : uint32_t
    {
        write = 1U << 16,
        read  = 1U << 17
    };

    enum class gbs_version : uint8_t
    {
        e40 = 0,
        e10 = 1,
        e100 = 2
    };

    eth_ctrl(przone_interface::ptr_t przone,  gbs_version version);
    virtual ~eth_ctrl();
    virtual bool read(uint32_t address, uint32_t instance, uint32_t & value);
    virtual bool write(uint32_t address, uint32_t instance, uint32_t value);
    template<typename T>
    bool read(T address, uint32_t instance, uint32_t & value)
    {
        return read(static_cast<uint32_t>(address), instance, value);
    }

    template<typename T>
    bool write(T address, uint32_t instance, uint32_t value)
    {
        return write(static_cast<uint32_t>(address), instance, value);
    }

private:
    przone_interface::ptr_t przone_;
    uint32_t scratch_;
    uint32_t eth_arst_;
    uint32_t eth_ctrl_addr_;
    uint32_t eth_wr_data_;
    uint32_t eth_rd_data_;
};

} // end of namespace hssi
} // end of namespace fpga
} // end of namespace intel

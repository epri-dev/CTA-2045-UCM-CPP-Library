// =====================================================================================
// Copyright (c) 2016, Electric Power Research Institute (EPRI)
// All rights reserved.
//
// libcea2045 ("this software") is licensed under BSD 3-Clause license.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// *  Neither the name of EPRI nor the names of its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
// OF SUCH DAMAGE.
//
// This EPRI software incorporates work covered by the following copyright and permission
// notices. You may not use these works except in compliance with their respective
// licenses, which are provided below.
//
// These works are provided by the copyright holders and contributors "as is" and any express or
// implied warranties, including, but not limited to, the implied warranties of merchantability
// and fitness for a particular purpose are disclaimed.
//
// This software relies on the following libraries and licenses:
//
// #########################################################################################
// Boost Software License, Version 1.0
// #########################################################################################
//
// * catch++ v1.2.1 (https://github.com/philsquared/Catch)
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// #########################################################################################
// MIT Licence
// #########################################################################################
//
// * easylogging++ Copyright (c) 2017 muflihun.com
//   https://github.com/easylogging/easyloggingpp
//   https://easylogging.muflihun.com
//   https://muflihun.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
/*
 * CEA2045CommodityResponse.h
 *
 *  Created on: Mar 10, 2015
 *      Author: rgause
 */

#ifndef CEA2045MESSAGECOMMODITYRESPONSE_H_
#define CEA2045MESSAGECOMMODITYRESPONSE_H_

#include <endian.h>
#include <stdint.h>
#include "CEA2045MessageMacros.h"

namespace cea2045 {

// TODO: verify that this is the longest possible commodity response message
#define CEA2045_MAX_COMMODITY_RESPONSE_LENGTH 101

struct cea2045CommodityData
{
	unsigned char commodityCode;
	unsigned char instantaneousRate[6];
	unsigned char cumulativeAmount[6];

	int64_t getInstantaneousRate()
	{
		return ((int64_t)instantaneousRate[0] << 40) +
				((int64_t)instantaneousRate[1] << 32) +
				((int64_t)instantaneousRate[2] << 24) +
				((int64_t)instantaneousRate[3] << 16) +
				((int64_t)instantaneousRate[4] << 8) +
				((int64_t)instantaneousRate[5]);
	}

	int64_t getCumulativeAmount()
	{
		return ((int64_t)cumulativeAmount[0] << 40) +
				((int64_t)cumulativeAmount[1] << 32) +
				((int64_t)cumulativeAmount[2] << 24) +
				((int64_t)cumulativeAmount[3] << 16) +
				((int64_t)cumulativeAmount[4] << 8) +
				((int64_t)cumulativeAmount[5]);
	}
};

struct cea2045CommodityResponse
{
	unsigned char msgType1;
	unsigned char msgType2;
	unsigned short length;
	unsigned char opCode1;
	unsigned char opCode2;
	unsigned char responseCode;

	cea2045CommodityData commodityData[7];

	unsigned short checksum;

	MACRO_LENGTH
	MACRO_CHECKSUM

	unsigned short getCommodityDataCount()
	{
		return (getLength() / sizeof(cea2045CommodityData));
	}

	cea2045CommodityData *getCommodityData(int index)
	{
		int count = getCommodityDataCount();

		if (index > count - 1)
			return nullptr;

		unsigned char *buffer = (unsigned char *)(&msgType1);

		// commodity response header is 7 bytes
		return (cea2045CommodityData *)((buffer + 7) + index * sizeof(cea2045CommodityData));
	}

}__attribute__((packed));

} // namespace cea2045

#endif /* CEA2045MESSAGECOMMODITYRESPONSE_H_ */

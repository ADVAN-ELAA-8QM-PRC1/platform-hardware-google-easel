/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HDR_PLUS_CLIENT_LISTENER_H
#define HDR_PLUS_CLIENT_LISTENER_H

#include "hardware/camera3.h"
#include "HdrPlusTypes.h"

namespace android {


class HdrPlusClient;

/*
 * HdrPlusClientListener defines callbacks that will be invoked by HdrPlusClient for events like
 * returning capture results.
 */
class HdrPlusClientListener {
public:
    virtual ~HdrPlusClientListener() {};

    /*
     * Invoked when an HDR+ client is opened successfully via
     * EaselManagerClient::openHdrPlusClientAsync.
     */
    virtual void onOpened(std::unique_ptr<HdrPlusClient> client) = 0;

    /*
     * Invoked when opening an HDR+ client failed via EaselManagerClient::openHdrPlusClientAsync.
     *
     * err is
     *  -EEXIST:    if an HDR+ client is already opened.
     *  -ENODEV:    if opening an HDR+ failed due to a serious error.
     */
    virtual void onOpenFailed(status_t err) = 0;

    /*
     * Invoked when HDR+ client is in a fatal error state. After receiving this error, calls to HDR+
     * client will not succeed and HDR+ client should be closed.
     */
    virtual void onFatalError() = 0;

    /*
     * Invoked when a CaptureResult, containing a subset or all output buffers for a CaptureRequest,
     * is received. This may be invoked multiple times for one CaptureRequest but each CaptureResult
     * will contain distinct output buffers that have not been received yet.
     */
    virtual void onCaptureResult(pbcamera::CaptureResult *result,
            const camera_metadata_t &resultMetadata) = 0;

    /*
     * Invoked when a failed CaptureResult, containing a subset or all output buffers for a
     * CaptureRequest, is received. Output buffers in a failed capture result may contain garbage
     * data. This may be invoked multiple times for one CaptureRequest but each CaptureResult
     * will contain distinct output buffers that have not been received yet.
     */
    virtual void onFailedCaptureResult(pbcamera::CaptureResult *failedResult) = 0;
};

} // namespace android

#endif // HDR_PLUS_CLIENT_LISTENER_H

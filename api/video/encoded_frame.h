/*
 *  Copyright (c) 2016 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef API_VIDEO_ENCODED_FRAME_H_
#define API_VIDEO_ENCODED_FRAME_H_

#include <stddef.h>
#include <stdint.h>

#include "modules/video_coding/encoded_frame.h"

namespace webrtc {
namespace video_coding {

// TODO(bugs.webrtc.org/12206): Remove when downstream has been updated.
struct VideoLayerFrameId {
  int64_t picture_id = -1;
};

// TODO(philipel): Remove webrtc::VCMEncodedFrame inheritance.
// TODO(philipel): Move transport specific info out of EncodedFrame.
// NOTE: This class is still under development and may change without notice.
class EncodedFrame : public webrtc::VCMEncodedFrame {
 public:
  static const uint8_t kMaxFrameReferences = 5;

  EncodedFrame() = default;
  EncodedFrame(const EncodedFrame&) = default;
  virtual ~EncodedFrame() {}

  // When this frame was received.
  virtual int64_t ReceivedTime() const = 0;

  // When this frame should be rendered.
  virtual int64_t RenderTime() const = 0;

  // This information is currently needed by the timing calculation class.
  // TODO(philipel): Remove this function when a new timing class has
  //                 been implemented.
  virtual bool delayed_by_retransmission() const;

  bool is_keyframe() const { return num_references == 0; }

  // TODO(bugs.webrtc.org/12206): Replace with private int64_t when downstream
  //                              has been updated.
  VideoLayerFrameId id;

  void SetId(int64_t frame_id) { id.picture_id = frame_id; }
  int64_t Id() const { return id.picture_id; }

  // TODO(philipel): Add simple modify/access functions to prevent adding too
  // many |references|.
  size_t num_references = 0;
  int64_t references[kMaxFrameReferences];
  // Is this subframe the last one in the superframe (In RTP stream that would
  // mean that the last packet has a marker bit set).
  bool is_last_spatial_layer = true;
};

}  // namespace video_coding
}  // namespace webrtc

#endif  // API_VIDEO_ENCODED_FRAME_H_

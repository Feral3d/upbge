/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Copyright 2020, Blender Foundation.
 */

/** \file
 * \ingroup gpu
 */

#pragma once

#include "MEM_guardedalloc.h"

#include "BLI_utildefines.h"

#include "gpu_state_private.hh"

#include "glew-mx.h"

namespace blender {
namespace gpu {

class GLFrameBuffer;
class GLTexture;

/**
 * State manager keeping track of the draw state and applying it before drawing.
 * Opengl Implementation.
 **/
class GLStateManager : public GPUStateManager {
 public:
  /** Anothter reference to tje active framebuffer. */
  GLFrameBuffer *active_fb;

 private:
  /** Current state of the GL implementation. Avoids resetting the whole state for every change. */
  GPUState current_;
  GPUStateMutable current_mutable_;
  /** Limits. */
  float line_width_range_[2];

  /** Texture state:
   * We keep the full stack of textures and sampler bounds to use multi bind, and to be able to
   * edit and restore texture binds on the fly without querying the context.
   * Also this allows us to keep track of textures bounds to many texture units.
   * Keep the targets to know what target to set to 0 for unbinding (legacy).
   * Init first target to GL_TEXTURE_2D for texture_bind_temp to work.
   */
  GLuint targets_[64] = {GL_TEXTURE_2D};
  GLuint textures_[64] = {0};
  GLuint samplers_[64] = {0};
  uint64_t dirty_texture_binds_ = 0;

 public:
  GLStateManager();

  void apply_state(void) override;

  void texture_bind(Texture *tex, eGPUSamplerState sampler, int unit) override;
  void texture_bind_temp(GLTexture *tex);
  void texture_unbind(Texture *tex) override;
  void texture_unbind_all(void) override;

  void texture_unpack_row_length_set(uint len) override;

  /* Game engine transition */
  void texture_bind_bge(Texture *tex, int unit);

  uint64_t bound_texture_slots(void);

 private:
  static void set_write_mask(const eGPUWriteMask value);
  static void set_depth_test(const eGPUDepthTest value);
  static void set_stencil_test(const eGPUStencilTest test, const eGPUStencilOp operation);
  static void set_stencil_mask(const eGPUStencilTest test, const GPUStateMutable state);
  static void set_clip_distances(const int new_dist_len, const int old_dist_len);
  static void set_logic_op(const bool enable);
  static void set_facing(const bool invert);
  static void set_backface_culling(const eGPUFaceCullTest test);
  static void set_provoking_vert(const eGPUProvokingVertex vert);
  static void set_shadow_bias(const bool enable);
  static void set_blend(const eGPUBlend value);

  void set_state(const GPUState &state);
  void set_mutable_state(const GPUStateMutable &state);

  void texture_bind_apply(void);

  MEM_CXX_CLASS_ALLOC_FUNCS("GLStateManager")
};

}  // namespace gpu
}  // namespace blender

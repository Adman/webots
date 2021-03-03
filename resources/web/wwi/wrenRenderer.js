// Copyright 1996-2021 Cyberbotics Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import {WbWorld} from './nodes/wbWorld.js';
import {disableShadows} from './nodes/wbPreferences.js';

class WrenRenderer {
  constructor() {
    this.canvas = document.createElement('canvas');
    this.canvas.id = 'canvas';
    let div = document.getElementById('view3d');

    if (typeof div === 'undefined' || div === null)
      div = document.getElementById('playerDiv');
    div.insertBefore(this.canvas, div.firstChild);

    _wr_config_enable_shadows(!disableShadows);

    // glGetError causes freeze with Firefox on Windows 10
    _wr_gl_state_disable_check_error();
  }

  setSize(width, height) {
    canvas.width = width;
    canvas.height = height;
  }

  render() {
    if (!_wr_gl_state_is_initialized())
      return;

    try {
      WbWorld.instance.viewpoint.updatePostProcessingParameters();

      _wr_scene_render(_wr_scene_get_instance(), null, true);
      // console.log("render");
    } catch (error) {
      console.log('No Context');
    }
  }

  renderMinimal() {
    if (!_wr_gl_state_is_initialized())
      return;

    try {
      _wr_scene_render(_wr_scene_get_instance(), null, true);
    } catch (error) {
      console.log('No Context');
    }
  }
}

export {WrenRenderer};

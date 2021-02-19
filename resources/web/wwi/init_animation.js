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
import {webots} from './webots.js';

function init() {
  const name = location.pathname.substring(location.pathname.lastIndexOf('/') + 1).replace('.html', '');
  let view = new webots.View(document.getElementById('playerDiv'));
  view.open(name + '.x3d');
  view.setAnimation(name + '.json', 'play', true);
}

if (!!window.chrome)
  init();
else {
  Module['onRuntimeInitialized'] = function() {
    console.log('wasm loaded ');
    init();
  };
}

if (location.protocol === 'file:' && (!!window.chrome && !!window.chrome.webstore))
  alert('Webots HTML5 Models and Animations cannot be loaded locally on Google Chrome, as Chrome does not support cross-origin requests using the file:// protocol.');

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
 */

/** \file \ingroup freestyle
 */

#ifndef __FREESTYLE_PYTHON_BBOX_H__
#define __FREESTYLE_PYTHON_BBOX_H__

extern "C" {
#include <Python.h>
}

#include "../geometry/BBox.h"
#include "../geometry/Geom.h"

using namespace Freestyle;
using namespace Freestyle::Geometry;

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////

extern PyTypeObject BBox_Type;

#define BPy_BBox_Check(v) (PyObject_IsInstance((PyObject *)v, (PyObject *)&BBox_Type))

/*---------------------------Python BPy_BBox structure definition----------*/
typedef struct {
	PyObject_HEAD
	BBox<Vec3r> *bb;
} BPy_BBox;

/*---------------------------Python BPy_BBox visible prototypes-----------*/

int BBox_Init(PyObject *module);


///////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif


#endif /* __FREESTYLE_PYTHON_BBOX_H__ */

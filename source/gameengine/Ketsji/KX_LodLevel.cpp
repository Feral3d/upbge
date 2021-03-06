/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
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
 * Contributor(s): Ulysse Martin, Tristan Porteries.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file gameengine/Ketsji/KX_LodLevel.cpp
 *  \ingroup ketsji
 */

#include "KX_LodLevel.h"

#include "KX_MeshProxy.h"

KX_LodLevel::KX_LodLevel(float distance,
                         float hysteresis,
                         unsigned short level,
                         RAS_MeshObject *meshobj,
                         unsigned short flag)
    : m_distance(distance),
      m_hysteresis(hysteresis),
      m_level(level),
      m_flags(flag),
      m_meshobj(meshobj)
{
}

KX_LodLevel::~KX_LodLevel()
{
}

float KX_LodLevel::GetDistance() const
{
  return m_distance;
}

float KX_LodLevel::GetHysteresis() const
{
  return m_hysteresis;
}

unsigned short KX_LodLevel::GetLevel() const
{
  return m_level;
}

unsigned short KX_LodLevel::GetFlag() const
{
  return m_flags;
}

RAS_MeshObject *KX_LodLevel::GetMesh() const
{
  return m_meshobj;
}

#ifdef WITH_PYTHON

PyTypeObject KX_LodLevel::Type = {PyVarObject_HEAD_INIT(nullptr, 0) "KX_LodLevel",
                                  sizeof(PyObjectPlus_Proxy),
                                  0,
                                  py_base_dealloc,
                                  0,
                                  0,
                                  0,
                                  0,
                                  py_base_repr,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  Methods,
                                  0,
                                  0,
                                  &CValue::Type,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  0,
                                  py_base_new};

PyMethodDef KX_LodLevel::Methods[] = {
    {nullptr, nullptr}  // Sentinel
};

PyAttributeDef KX_LodLevel::Attributes[] = {
    KX_PYATTRIBUTE_RO_FUNCTION("mesh", KX_LodLevel, pyattr_get_mesh),
    KX_PYATTRIBUTE_SHORT_RO("level", KX_LodLevel, m_level),
    KX_PYATTRIBUTE_FLOAT_RO("distance", KX_LodLevel, m_distance),
    KX_PYATTRIBUTE_FLOAT_RO("hysteresis", KX_LodLevel, m_hysteresis),
    KX_PYATTRIBUTE_RO_FUNCTION("useHysteresis", KX_LodLevel, pyattr_get_use_hysteresis),
    KX_PYATTRIBUTE_RO_FUNCTION("useMesh", KX_LodLevel, pyattr_get_use_mesh),
    KX_PYATTRIBUTE_RO_FUNCTION("useMaterial", KX_LodLevel, pyattr_get_use_material),
    KX_PYATTRIBUTE_NULL  // Sentinel
};

PyObject *KX_LodLevel::pyattr_get_mesh(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef)
{
  KX_LodLevel *self = static_cast<KX_LodLevel *>(self_v);
  KX_MeshProxy *meshproxy = new KX_MeshProxy(self->GetMesh());
  return meshproxy->NewProxy(true);
}

PyObject *KX_LodLevel::pyattr_get_use_hysteresis(PyObjectPlus *self_v,
                                                 const KX_PYATTRIBUTE_DEF *attrdef)
{
  KX_LodLevel *self = static_cast<KX_LodLevel *>(self_v);
  return PyBool_FromLong(self->GetFlag() & KX_LodLevel::USE_HYSTERESIS);
}

PyObject *KX_LodLevel::pyattr_get_use_mesh(PyObjectPlus *self_v, const KX_PYATTRIBUTE_DEF *attrdef)
{
  KX_LodLevel *self = static_cast<KX_LodLevel *>(self_v);
  return PyBool_FromLong(self->GetFlag() & KX_LodLevel::USE_MESH);
}

PyObject *KX_LodLevel::pyattr_get_use_material(PyObjectPlus *self_v,
                                               const KX_PYATTRIBUTE_DEF *attrdef)
{
  KX_LodLevel *self = static_cast<KX_LodLevel *>(self_v);
  return PyBool_FromLong(self->GetFlag() & KX_LodLevel::USE_MATERIAL);
}

#endif  // WITH_PYTHON

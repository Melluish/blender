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

#ifndef __BLI_BOOLEAN_HH__
#define __BLI_BOOLEAN_HH__

/** \file
 * \ingroup bli
 */

#include "BLI_mesh_intersect.hh"
#include <functional>

namespace blender::meshintersect {

/* Enum values after BOOLEAN_NONE need to match BMESH_ISECT_BOOLEAN_... values in
 * editmesh_intersect.c. */
enum bool_optype {
  BOOLEAN_NONE = -1,
  /* Aligned with BooleanModifierOp. */
  BOOLEAN_ISECT = 0,
  BOOLEAN_UNION = 1,
  BOOLEAN_DIFFERENCE = 2,
};

/* Do the boolean operation op on the mesh pm_in.
 * The boolean operation has nshapes input shapes. Each is a disjoint subset of the input mesh.
 * The shape_fn argument, when applied to an input face argument, says which shape it is in
 * (should be a value from -1 to nshapes - 1: if -1, it is not part of any shape).
 * The use_self arg says whether or not the function should assume that faces in the
 * same shape intersect - if the argument is true, such self-intersections will be found.
 * Sometimes the caller has already done a triangulation of the faces,
 * and if so, *pm_triangulated contains a triangulation: if non-null, it contains a mesh
 * of triangles, each of whose orig_field says which face in pm that triangle belongs to.
 * pm arg isn't const because we may populate its verts (for debugging).
 * Same goes for the pm_triangulated arg.
 * The output Mesh will have faces whose orig fields map back to faces and edges in
 * the input mesh.
 */
Mesh boolean_mesh(Mesh &pm,
                  bool_optype op,
                  int nshapes,
                  std::function<int(int)> shape_fn,
                  bool use_self,
                  Mesh *pm_triangulated,
                  MArena *arena);

/* This is like boolean, but operates on Mesh's whose faces are all triangles.
 * It is exposed mainly for unit testing, at the moment: boolean_mesh() uses
 * it to do most of its work.
 */
Mesh boolean_trimesh(Mesh &tm,
                     bool_optype op,
                     int nshapes,
                     std::function<int(int)> shape_fn,
                     bool use_self,
                     MArena *arena);

}  // namespace blender::meshintersect
#endif /* __BLI_BOOLEAN_HH__ */
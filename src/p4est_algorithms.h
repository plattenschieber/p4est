
#ifndef __P4EST_ALGORITHMS_H__
#define __P4EST_ALGORITHMS_H__

#include <p4est.h>

/** Compare two quadrants in their Morton ordering.
 * \return Returns < 0 if \a v1 < \a v2,
 *                   0 if \a v1 == \a v2,
 *                 > 0 if \a v1 > \a v2
 */
int                 p4est_quadrant_compare (const void *v1, const void *v2);

/** Compute the position of this child within its siblings.
 * \return Returns its child id in 0..3
 */
int                 p4est_quadrant_child_id (const p4est_quadrant_t * q);

/** Test if a quadrant has valid Morton indices.
 * \param [in] q Quadrant to be tested.
 * \return Returns 1 if \a q is valid.
 */
int                 p4est_quadrant_is_valid (const p4est_quadrant_t * q);

/** Test if two quadrants have equal Morton indices.
 * \return 1 if \a q1 describes the same quadrant as \a q2.
 */
int                 p4est_quadrant_is_equal (const p4est_quadrant_t * q1,
                                             const p4est_quadrant_t * q2);

/** Test if two quadrants are siblings.
 * \param [in] q1 First quadrant to be tested.
 * \param [in] q2 Second quadrant to be tested.
 * \return 1 if \a q1 is unequal to and a sibling of \a q2.
 */
int                 p4est_quadrant_is_sibling (const p4est_quadrant_t * q1,
                                               const p4est_quadrant_t * q2);

/** Test if two quadrants are siblings.
 * Descriptive, slower version of \a p4est_quadrant_is_sibling.
 * For debugging and educational purposes only.
 */
int                 p4est_quadrant_is_sibling_D (const p4est_quadrant_t * q1,
                                                 const p4est_quadrant_t * q2);

/** Test if a quadrant it the parent of another quadrant.
 * \param [in] q Quadrant to be tested.
 * \param [in] r Possible child quadrant.
 * \return 1 if \a q is the parent of \a r.
 */
int                 p4est_quadrant_is_parent (const p4est_quadrant_t * q,
                                              const p4est_quadrant_t * r);

/** Test if a quadrant it the parent of another quadrant.
 * Descriptive, slower version of \a p4est_quadrant_is_parent.
 * For debugging and educational purposes only.
 */
int                 p4est_quadrant_is_parent_D (const p4est_quadrant_t * q,
                                                const p4est_quadrant_t * r);

/** Test if a quadrant is an ancestor of another quadrant.
 * \param [in] q Quadrant to be tested.
 * \param [in] r Descendent quadrant.
 * \return 1 if \a q isunequal to and an ancestor of \a r.
 */
int                 p4est_quadrant_is_ancestor (const p4est_quadrant_t * q,
                                                const p4est_quadrant_t * r);

/** Test if a quadrant is an ancestor of another quadrant.
 * Descriptive, slower version of \a p4est_quadrant_is_ancestor.
 * For debugging and educational purposes only.
 */
int                 p4est_quadrant_is_ancestor_D (const p4est_quadrant_t * q,
                                                  const p4est_quadrant_t * r);

/** Compute the parent of a quadrant.
 * \param [in]  q Input quadrant.
 * \param [in,out] r Existing quadrant whose Morton index will be filled
 *                   with the Morton index of the parent of \a q.
 *                   Its user_data will be untouched.
 * \note \a q may point to the same quadrant as \a r.
         The user_data of \a r is never modified.
 */
void                p4est_quadrant_parent (const p4est_quadrant_t * q,
                                           p4est_quadrant_t * r);

/** Compute the 4 children of a quadrant.
 * \param [in]     q  Input quadrant.
 * \param [in,out] c0 First computed child.
 *                    \a q may point to the same quadrant as \a c0.
 * \note The user_data of \a c0, c1, c2, c3 is never modified.
 */
void                p4est_quadrant_children (const p4est_quadrant_t * q,
                                             p4est_quadrant_t * c0,
                                             p4est_quadrant_t * c1,
                                             p4est_quadrant_t * c2,
                                             p4est_quadrant_t * c3);

/** Computes the nearest common ancestor of two quadrants.
 * \param [in]     q1 First input quadrant.
 * \param [in]     q2 Second input quadrant.
 * \param [in,out] r Existing quadrant whose Morton index will be filled.
 *                   Its user_data will be untouched.
 * \note \a q1, \a q2, \a r may point to the same quadrant.
 *       The user_data of \a r is never modified.
 */
void                p4est_nearest_common_ancestor (const p4est_quadrant_t *
                                                   q1,
                                                   const p4est_quadrant_t *
                                                   q2, p4est_quadrant_t * r);

/** Computes the nearest common ancestor of two quadrants.
 * Descriptive, slower version of \a p4est_nearest_common_ancestor.
 * For debugging and educationial purposes only.
 */
void                p4est_nearest_common_ancestor_D (const p4est_quadrant_t *
                                                     q1,
                                                     const p4est_quadrant_t *
                                                     q2,
                                                     p4est_quadrant_t * r);

/** Set quadrant Morton indices based on linear index in uniform grid.
 * \param [in,out] Quadrant whose Morton indices will be set.
 * \note Uniform grid implies level < 16 and thus morton_xy < INT32_MAX.
 *       The user_data of \a quadrant is never modified.
 */
void                p4est_quadrant_set_morton (p4est_quadrant_t * quadrant,
                                               int8_t level, int32_t index);

/** Alloc and initialize the user data of a valid quadrant.
 * \param [in]  which_tree 0-based index of this quadrant's tree.
 * \param [in,out]  quad       The quadrant to be initialized.
 * \param [in]  init_fn    User-supplied callback function to init data.
 */
void                p4est_quadrant_init_data (p4est_t * p4est,
                                              int32_t which_tree,
                                              p4est_quadrant_t * quad,
                                              p4est_init_t init_fn);

/** Free the user data of a valid quadrant.
 * \param [in,out]  quad The quadrant whose data shall be freed.
 */
void                p4est_quadrant_free_data (p4est_t * p4est,
                                              p4est_quadrant_t * quad);

/** Test if a tree is sorted in Morton ordering.
 * \return Returns 1 if sorted, 0 otherwise.
 */
int                 p4est_tree_is_sorted (p4est_tree_t * tree);

/** Print the quadrants in a tree.
 * Prints one line per quadrant with x, y, level and a string.
 * The string denotes the relation to the previous quadrant and can be:
 *   I   for identical quadrants
 *   R   for a quadrant that with smaller Morton index
 *   Cn  for child id n
 *   Sn  for sibling with child id n
 *   D   for a descendent
 *   Qn  for a general quadrant whose child id is n
 * \param [in] tree        Any (possibly incomplete, unsorted) tree to be printed.
 * \param [in] identifier  If >= 0, each line is prefixed by "[identifier] "
 * \param [in] nout        Stream to print to. May be NULL, then nothing happens.
 */
void                p4est_tree_print (p4est_tree_t * tree, int identifier,
                                      FILE * nout);

/** Constructs a minimal linear octree between two octants.
 *
 * This is alogorithm 2 from H. Sundar, R.S. Sampath and G. Biros.
 *
 * \pre \a q1 < \a q2 in the Morton ordering.
 *
 * \param [in] p43est used for the memory polls and quadrant init.
 * \param [in]  q1         First input quadrant.  The user data will not change.
 * \param [in]  include_q1 Flag is set to 1 if q1 is included.
 * \param [in]  q2         First input quadrant.  The user data will not change.
 * \param [in]  include_q2 Flag is set to 1 if q2 is included.
 * \param [out] tree       Initialized tree with zero elements.
 * \param [in]  which_tree The 0-based index of \a tree which is needed for
 *                         the \c p4est_quadrant_init_data routine.
 * \param [in] init_fn   Callback function to initialize the user_data
 *                       which is already allocated automatically.
 */
void                p4est_complete_region (p4est_t * p4est,
                                           const p4est_quadrant_t * q1,
                                           int include_q1,
                                           const p4est_quadrant_t * q2,
                                           int include_q2,
                                           p4est_tree_t * tree,
                                           int32_t which_tree,
                                           p4est_init_t init_fn);

#endif /* !__P4EST_ALGORITHMS_H__ */

//
// Created by dunka on 27.09.2019.
//

#ifndef MIPT_DED_32_ASSERT_H
#define MIPT_DED_32_ASSERT_H

/*!
 * My assert
 */
#define ASSERT( cond )                                                                                                                    \
        if ( cond == 0 )                                                                                                                  \
        {                                                                                                                                 \
            printf ( "Assertion failed: Error %s, FILE %s, In function %s, Line %d\n", #cond, __FILE__, __PRETTY_FUNCTION__, __LINE__ );  \
            abort ();                                                                                                                     \
        }


#endif //MIPT_DED_32_ASSERT_H

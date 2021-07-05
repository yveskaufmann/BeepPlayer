/*
 * AlleMeineEntchen.h
 *
 *  Created on: 01.03.2014
 *      Author: Yves Kaufmann
 */

#ifndef ALLEMEINEENTCHEN_H_
#define ALLEMEINEENTCHEN_H_

#include "../BeepPlayer.h"

namespace BeepPlayer {
	namespace ExampleSongs {

		const Song AlleMeineEntchen = {1000, {
				{NoteFrequencie::D_l, NoteValue::V4},
				{NoteFrequencie::E_l, NoteValue::V4},
				{NoteFrequencie::F_l, NoteValue::V4},
				{NoteFrequencie::G_l, NoteValue::V4},
				{NoteFrequencie::A_l, NoteValue::V2},
				{NoteFrequencie::A_l, NoteValue::V2},

				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::A_l, NoteValue::V2},
				{NoteFrequencie::PAUSE, NoteValue::V2},

				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::H_l, NoteValue::V4},
				{NoteFrequencie::A_l, NoteValue::V2},
				{NoteFrequencie::PAUSE, NoteValue::V2},

				{NoteFrequencie::G_l, NoteValue::V4},
				{NoteFrequencie::G_l, NoteValue::V4},
				{NoteFrequencie::G_l, NoteValue::V4},
				{NoteFrequencie::G_l, NoteValue::V4},
				{NoteFrequencie::F_l, NoteValue::V2},
				{NoteFrequencie::F_l, NoteValue::V2},

				{NoteFrequencie::A_l, NoteValue::V4},
				{NoteFrequencie::A_l, NoteValue::V4},
				{NoteFrequencie::A_l, NoteValue::V4},
				{NoteFrequencie::A_l, NoteValue::V4},
				{NoteFrequencie::D_l, NoteValue::V2}
		}};
	}
}

#endif /* ALLEMEINEENTCHEN_H_ */

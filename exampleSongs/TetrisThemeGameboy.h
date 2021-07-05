/*
 * TetrisTheme.h
 *
 *  Created on: 02.03.2014
 *      Author: Yves Kaufmann
 */

#ifndef TETRISTHEMEGAMEBOY_H_
#define TETRISTHEMEGAMEBOY_H_

#include "../BeepPlayer.h"

namespace BeepPlayer {
	namespace ExampleSongs {

		const Song TetrisGameBoyTheme = {1700, {
				{NoteFrequencie::E_ll, 	NoteValue::V4},
				{NoteFrequencie::H_l, 	NoteValue::V8},
				{NoteFrequencie::C_ll, 	NoteValue::V8},
				{NoteFrequencie::D_ll, 	NoteValue::V4},
				{NoteFrequencie::C_ll, 	NoteValue::V8},
				{NoteFrequencie::H_l, 	NoteValue::V8},

				{NoteFrequencie::A_l, 	NoteValue::V4},
				{NoteFrequencie::A_l, 	NoteValue::V8},
				{NoteFrequencie::C_ll, 	NoteValue::V8},
				{NoteFrequencie::E_ll, 	NoteValue::V4},
				{NoteFrequencie::D_ll, 	NoteValue::V8},
				{NoteFrequencie::C_ll, 	NoteValue::V8},

				{NoteFrequencie::H_l, 	NoteValue::V4.getDotValue()},
				{NoteFrequencie::C_ll,	NoteValue::V8},
				{NoteFrequencie::D_ll, 	NoteValue::V4},
				{NoteFrequencie::E_ll,	NoteValue::V4},

				{NoteFrequencie::C_ll, 	NoteValue::V4},
				{NoteFrequencie::A_l, 	NoteValue::V4},
				{NoteFrequencie::A_l, 	NoteValue::V8},
				{NoteFrequencie::A_l, 	NoteValue::V8},
				{NoteFrequencie::H_l, 	NoteValue::V8},
				{NoteFrequencie::C_ll, 	NoteValue::V8},
				/* Line two */
				{NoteFrequencie::D_ll, 	NoteValue::V4.getDotValue()},
				{NoteFrequencie::F_ll, 	NoteValue::V8},
				{NoteFrequencie::A_ll, 	NoteValue::V4},
				{NoteFrequencie::G_ll, 	NoteValue::V8},
				{NoteFrequencie::F_ll, 	NoteValue::V8},

				{NoteFrequencie::E_ll, 	NoteValue::V4.getDotValue()},
				{NoteFrequencie::C_ll, 	NoteValue::V8},
				{NoteFrequencie::E_ll, 	NoteValue::V4},
				{NoteFrequencie::D_ll, 	NoteValue::V8},
				{NoteFrequencie::C_ll, 	NoteValue::V8},

				{NoteFrequencie::H_l, 	NoteValue::V4},
				{NoteFrequencie::H_l, 	NoteValue::V8},
				{NoteFrequencie::C_ll, 	NoteValue::V8},
				{NoteFrequencie::D_ll, 	NoteValue::V4},
				{NoteFrequencie::E_ll, 	NoteValue::V4},

				{NoteFrequencie::C_ll, 	NoteValue::V4},
				{NoteFrequencie::A_l, 	NoteValue::V4},
				{NoteFrequencie::A_l, 	NoteValue::V4},
				{NoteFrequencie::PAUSE, NoteValue::V4},
				/* Line three */
				{NoteFrequencie::E_ll, 	NoteValue::V2},
				{NoteFrequencie::C_ll, 	NoteValue::V2},

				{NoteFrequencie::D_ll, 	NoteValue::V2},
				{NoteFrequencie::H_l, 	NoteValue::V2},

				{NoteFrequencie::C_ll, 	NoteValue::V2},
				{NoteFrequencie::A_l, 	NoteValue::V2},

				{NoteFrequencie::Gis_l, NoteValue::V2},
				{NoteFrequencie::H_l, 	NoteValue::V4},
				{NoteFrequencie::PAUSE, NoteValue::V4},

				{NoteFrequencie::E_ll, 	NoteValue::V2},
				{NoteFrequencie::C_ll, 	NoteValue::V2},

				{NoteFrequencie::D_ll, 	NoteValue::V2},
				{NoteFrequencie::H_l, 	NoteValue::V2},

				{NoteFrequencie::C_ll, 	NoteValue::V4},
				{NoteFrequencie::E_ll, 	NoteValue::V4},
				{NoteFrequencie::A_ll, 	NoteValue::V2},

				{NoteFrequencie::Gis_ll,NoteValue::V2},
				{NoteFrequencie::PAUSE, NoteValue::V2},
		}};
	}
}

#endif /* TETRISTHEME_H_ */

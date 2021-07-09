/**
	Beep Player library header declaration

	Project: MonoBeepSoundPlayer
	File: BeepPlayer.h
	Purpose: Declare Beep Player Types/Classes

	@author fxdapokalypse
	@version 1.0 11.03.2014
*/

#ifndef BEEP_PLAYER_H_
#define BEEP_PLAYER_H_

#include <vector>
#include <string>

namespace BeepPlayer
{
	/**
	 *  Set of notes with their frequency values.
	 */
	enum class NoteFrequencie : int
	{
		PAUSE = -1,
		C_l = 261,
		D_l = 293,
		E_l = 329,
		F_l = 349,
		G_l = 391,
		Gis_l = 415,
		A_l = 440,
		H_l = 493,
		C_ll = 523,
		D_ll = 587,
		E_ll = 659,
		F_ll = 698,
		G_ll = 783,
		Gis_ll = 830,
		A_ll = 880,
		H_ll = 987
	};

	/**
	 * Type for NoteValue
	 */
	class NoteValue
	{
	public:
		/**
		 * Whole Note 4/4
		 */
		static const NoteValue V1;

		/**
		 * Half Note  1/2
		 */
		static const NoteValue V2;

		/**
		 * Quarter Note 1/4
		 */
		static const NoteValue V4;

		/**
		 * Eighth note 1/8
		 */
		static const NoteValue V8;

		/**
		 * Sixteenth Note 1/16
		 */
		static const NoteValue V16;

		/**
		 * Thirty-Second Note Note 1/32
		 */
		static const NoteValue V32;

		/**
		 * Initialize a note value
		 */

		NoteValue(const float &value);

		/**
		 * Return the note value
		 *
		 * @return The note value as float value.
		 */
		float getValue() const;
		/**
		 * Return the dot note value
		 *
		 * @return The dot note value as float value.
		 */
		float getDotValue() const;
		/**
		 * Caluculate the duration of note value in ms for a specific tact.
		 *
		 * @param tact The tact in ms.
		 * @return The duration of the note in ms.
		 */
		int getDurationBy(int tact);

	private:
		float value;
	};

	/**
	 * Calculate the dot value of a note.
	 *
	 * @param value Value of a given note.
	 * @return The dot Value of the given note.
	 */
	float dotNoteValue(float &value);

	/**
	 *  Data structure for a Note
	 */
	struct Note
	{
		/**
		 * Frequencie of the note
		 */
		NoteFrequencie frequence;
		/**
		 * Value of the note e.g.: 1/2, 1/4 Note
		 */
		NoteValue noteValue;
	};

	/**
	 * Data structure for a Song
	 */
	struct Song
	{
		/**
		 * Tact in ms
		 */
		int tact;
		/**
		 * Notes of  the song
		 */
		std::vector<Note> notes;
	};

	/**
	 * Play the specified song.
	 *
	 * @param song String representation of the song.
	 */
	void playSong(const std::string &song);

	/**
	 * Play the specified song.
	 *
	 * @param song Song structure with filled notes and durations.
	 */
	void playSong(const BeepPlayer::Song &song);

	/**
	 * Replay the current song after it was finished
	 */
	void repeatCurrentFinishedSong();

	/**
	 *  Starts the player
	 */
	void start();

	/**
	 *  Stops the player
	 */
	void stop();

	/**
	 *  Blocks the current thread until a song was fully played.
	 */
	void waitForSongCompletion();
};

#endif /* SONG_H_ */

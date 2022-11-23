package com.example.java;

import com.example.java.OutputUtils;
import org.jfugue.player.Player;
public class Out {
	public static void main(String[] args) {
		OutputUtils outputUtils = new OutputUtils();
		String nombreTrack = outputUtils.defineTrack();
		String nombreNote = new String();
		String nombreNote2 = new String();
		String nombreSong = outputUtils.defineSong();
		nombreNote = outputUtils.modifyNote("D", "q", 4);
		nombreNote2 = outputUtils.modifyNote("C", "q", 5);
		nombreTrack = outputUtils.trackAddNote(nombreTrack, nombreNote);
		nombreTrack = outputUtils.trackAddNote(nombreTrack, nombreNote2);
		nombreTrack = outputUtils.trackSubstraction(nombreTrack, nombreNote);
		nombreTrack = outputUtils.trackMultiply(nombreTrack, 2);
		nombreTrack = outputUtils.changeTempo(nombreTrack, 0.5);
		nombreTrack = outputUtils.changeInstrument(nombreTrack, 1);
		nombreSong = outputUtils.songAddTrack(nombreSong, nombreTrack);
		nombreSong = outputUtils.setSongDuration(nombreSong, 5);
		Player player = new Player();
		player.play(nombreSong);
	}
}

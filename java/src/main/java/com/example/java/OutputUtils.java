package com.example.java;
import org.jfugue.midi.MidiDictionary;
import org.jfugue.tools.ComputeDurationForEachTrackTool;
import org.staccato.StaccatoParser;

public class OutputUtils {

    private final String DEFAULT_TEMPO="T120";
    private final String DEFAULT_OCTAVE="4";
    private final String DEFAULT_DURATION="q";
    private final String DEFAULT_INSTRUMENT="I0";
    public String modifyNote(String note){
        return note.equals("R")? note+DEFAULT_DURATION : note+DEFAULT_OCTAVE+DEFAULT_DURATION;
    }
    public String modifyNote(String note,String rythm){
        if(rythm.equals("i"))
            rythm="qqq";
        return note.equals("R")? note+rythm: note+DEFAULT_OCTAVE+rythm;
    }
    public String modifyNote(String note,String rythm,int chord){
        if(rythm.equals("i"))
            rythm="qqq";
        return note+chord+rythm;
    }

    public String defineTrack(){
        return DEFAULT_TEMPO+' '+DEFAULT_INSTRUMENT+' ';
    }
    public String trackAddNote(String track,String note){
        return track+' '+note;
    }
    public String trackAddTrack(String track,String note){
        return track+' '+track;
    }

    public String defineSong(){
        return "";
    }
    public String songAddTrack(String song,String track){
        int tracksAmount=0;
        int index=0;
        while((index=song.indexOf('V',index))>=0){
            tracksAmount++;
            index++;}
        if(tracksAmount>15)
            throw new RuntimeException("LIMIT OF 16 TRACKS PER SONG SURPASSED");


        return song+" V"+String.valueOf(tracksAmount)+' '+track;
    }

    public String changeTempo(String track,double speed){
        StringBuilder changedSong=new StringBuilder(track);
        Integer tempoValue;
        for(int index=0;(index=changedSong.indexOf("T",index)) >=0;index++){
            tempoValue=0;
            while(changedSong.charAt(index+1)>='0'&& changedSong.charAt(index+1)<='9' ){
                tempoValue*=10;
                tempoValue+=Character.getNumericValue(changedSong.charAt(index+1));
                changedSong.deleteCharAt(index+1);

            }
            tempoValue=(int)(tempoValue*speed);
            changedSong.insert(index+1,tempoValue);
        }
        return changedSong.toString();
    }

    public String changeInstrument(String track,int num){
        StringBuilder changedSong=new StringBuilder(track);
        Instruments instrument=Instruments.values()[num];
        for(int index=0;(index=changedSong.indexOf("I",index)) >=0;index++){
            int lastIndex=changedSong.indexOf(" ",index);
            changedSong.replace(index+1,lastIndex,instrument.toString());
            index++;
        }
        return changedSong.toString();
    }

    public String trackSubstraction(String track,String note){
        int lastIndex=-1;
        StringBuilder stringBuilder=new StringBuilder(track);
        lastIndex=stringBuilder.lastIndexOf(note);
        if(lastIndex>=0)
            stringBuilder.delete(lastIndex,lastIndex+note.length());
        return stringBuilder.toString();
    }
    public String trackDivision(String track,String note){
        StringBuilder stringBuilder=new StringBuilder(track);
        for(int index=0;(index=stringBuilder.indexOf(note+' ',index))>=0;){
            stringBuilder.delete(index,index+note.length());
        }
        return stringBuilder.toString();
    }

    public String trackMultiply(String track,int value){
        StringBuilder stringBuilder=new StringBuilder(track);
        for(int i=0;i<value-1;i++){
            stringBuilder.append(' '+track);
        }
        return stringBuilder.toString();
    }

    public String setSongDuration(String song,int duration){
        StaccatoParser parser=new StaccatoParser();
        ComputeDurationForEachTrackTool tool=new ComputeDurationForEachTrackTool();
        parser.addParserListener(tool);
        parser.parse(song);
        double[] durations= tool.getDurations();
        double max=0;
        for (double num:durations
             ) {
            if (num>max)
                max=num;
        }
        return changeTempo(song,max/duration);
    }
    }
using System;
using System.Collections.Generic;
using System.Text;
using DotNetSpeech;

namespace TTS
{
    public static class speaker
    {
        public static void speak(string args)
        {
            DotNetSpeech.SpeechVoiceSpeakFlags SpFlags = DotNetSpeech.SpeechVoiceSpeakFlags.SVSFlagsAsync;

            DotNetSpeech.SpVoice Voice = new DotNetSpeech.SpVoice();

            try {

                Voice.Voice = Voice.GetVoices("Name=Microsoft Lili - Chinese (China)", "Language=409").Item(0);
            }
            catch(Exception ex)
            {
                try
                {
                    Voice.Voice = Voice.GetVoices("Name=Microsoft Simplified Chinese", "Language=408").Item(0);
                }
                catch (Exception wx)
                {
                    return;
                }
            }
            Voice.Rate = 4;

            Voice.Speak(args, SpFlags);
        }
    }
}

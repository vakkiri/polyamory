/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BaseSound.h"
#include "PAGlo.h"
#include "PAVoice.h"
#include "PAOscillator.h"

//==============================================================================
PolyamoryAudioProcessor::PolyamoryAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    gloInit();
    
    synth.clearVoices();
    for (int i = 0; i < NUM_OSCS; ++i)
        oscs.push_back(new PAOscillator());
        
    for (int i = 0; i < NUM_VOICES; ++i) {
        PAVoice* newVoice = new PAVoice();
        for (int osc = 0; osc < NUM_OSCS; ++osc)
            newVoice->addOsc(oscs[osc]);
            
        voices.push_back(newVoice);
        synth.addVoice(voices.back());
    }
    
    synth.clearSounds();
    synth.addSound(new BaseSound());
}

PolyamoryAudioProcessor::~PolyamoryAudioProcessor()
{
    while (!voices.empty()) {
        delete voices.back();
        voices.pop_back();
    }
    gloFinish();
}

//==============================================================================
const String PolyamoryAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PolyamoryAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PolyamoryAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PolyamoryAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PolyamoryAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PolyamoryAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PolyamoryAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PolyamoryAudioProcessor::setCurrentProgram (int index)
{
}

const String PolyamoryAudioProcessor::getProgramName (int index)
{
    return {};
}

void PolyamoryAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PolyamoryAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    gloSampleRate = (float) sampleRate;
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void PolyamoryAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PolyamoryAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PolyamoryAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool PolyamoryAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PolyamoryAudioProcessor::createEditor()
{
    return new PolyamoryAudioProcessorEditor (*this);
}

//==============================================================================
void PolyamoryAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PolyamoryAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void PolyamoryAudioProcessor::setOscCenter(int osc, float val) {
    oscs[osc]->setCenter(val);
}

void PolyamoryAudioProcessor::setOscFreq(int osc, float val) {
    oscs[osc]->setFreq(val);
}

void PolyamoryAudioProcessor::setOscPitch(int osc, float val) {
    oscs[osc]->setPitch(val);
}

void PolyamoryAudioProcessor::setOscLslope(int osc, float val) {
    oscs[osc]->setLslope(val);
}

void PolyamoryAudioProcessor::setOscRslope(int osc, float val) {
    oscs[osc]->setRslope(val);
}

void PolyamoryAudioProcessor::setOscLcurve(int osc, float val) {
    oscs[osc]->setLcurve(val);
}

void PolyamoryAudioProcessor::setOscRcurve(int osc, float val) {
    oscs[osc]->setRcurve(val);
}

void PolyamoryAudioProcessor::setOscLevel(int osc, float val) {
    oscs[osc]->setLevel(val);
}

void PolyamoryAudioProcessor::setOscNoise(int osc, float val) {
    oscs[osc]->setNoise(val);
}
        
void PolyamoryAudioProcessor::setA(float val) {
    for (auto voice : voices)
        voice->setADSRA(val);
}

void PolyamoryAudioProcessor::setD(float val) {
    for (auto voice : voices)
        voice->setADSRD(val);
}

void PolyamoryAudioProcessor::setS(float val) {
    for (auto voice : voices)
        voice->setADSRS(val);
}

void PolyamoryAudioProcessor::setR(float val) {
    for (auto voice : voices)
        voice->setADSRR(val);
}
    
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolyamoryAudioProcessor();
}

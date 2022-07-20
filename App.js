import React from 'react';
import { StatusBar } from 'expo-status-bar';
import { TouchableOpacity, StyleSheet, Text, View, Image } from 'react-native';
import axios from 'axios';

const baseUrl = 'http://192.168.18.21';

export default function App() {

  const onPress = (value) => () => {
    axios.get(`${baseUrl}/${value}`).then((response) => {
      console.log(response.data);
    }).catch(e => {
      console.log('error', JSON.stringify(e));
    })
  }

  return (
    <View style={styles.container}>

      <Text style={styles.title}>
        Inclusion Life App
      </Text>
      <StatusBar style="auto" />

      <View style={styles.buttoncontainer}>

        <TouchableOpacity
          style={styles.button}
          activeOpacity={0.5} onPress={onPress('F')}>
          <Image
            source={require('./assets/top-arrow.png')}
            style={styles.buttonImage}
          />
        </TouchableOpacity>

      </View>

      <View style={styles.buttoncontainer}>
      <TouchableOpacity
          style={styles.button}
          activeOpacity={0.5} onPress={onPress('E')}>
          <Image
            source={require('./assets/left-arrow.png')}
            style={styles.buttonImage}
          />
        </TouchableOpacity>

        <TouchableOpacity
          style={styles.button}
          activeOpacity={0.5} onPress={onPress('S')}>
          <Image
            source={require('./assets/stop.png')}
            style={styles.buttonImageStop}
          />
        </TouchableOpacity>


        <TouchableOpacity
          style={styles.button}
          activeOpacity={0.5} onPress={onPress('D')}>
          <Image
            source={require('./assets/right-arrow.png')}
            style={styles.buttonImage}
          />
        </TouchableOpacity>

      </View>

      <View style={styles.buttoncontainer}>
        <TouchableOpacity
          style={styles.button}
          activeOpacity={0.5} onPress={onPress('T')}>
          <Image
            source={require('./assets/down-arrow.png')}
            style={styles.buttonImage}
          />
        </TouchableOpacity>
      </View>

    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#ffd700',//'#FFFF',
    alignItems: 'center',
    justifyContent: 'center',
  },
   button: {
    flexDirection: 'row',
    alignItems: 'center',
    backgroundColor: '#FFFF',
    borderWidth: 0.5,
    borderColor: '#fff',
    height: 100,
    borderRadius: 5,
    margin: 5,
  },
  buttonImage: {
    padding: 10,
    margin: 5,
    height: 100,
    width: 100,
    resizeMode: 'stretch',
  },
  buttoncontainer: {
    flexDirection: 'row'
  },
  label: {
    color: '#FFF',
  },
  title: {
    fontSize: 40,
    fontWeight: "bold",
    position: 'absolute',
    top: 60,
  },
  buttonImageStop: {
    padding: 10,
    margin: 5,
    height: 100,
    width: 100,
    resizeMode: 'stretch',
    backgroundColor: '#ff0000',
  }
});

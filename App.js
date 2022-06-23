import React from 'react';
import { StatusBar } from 'expo-status-bar';
import { TouchableOpacity, StyleSheet, Text, View } from 'react-native';
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
      <StatusBar style="auto" />

      <TouchableOpacity style={styles.button} onPress={onPress('F')}>
        <Text style={styles.label} >Frente</Text>
      </TouchableOpacity>

      <TouchableOpacity style={styles.button} onPress={onPress('T')}>
        <Text style={styles.label}>Trás</Text>
      </TouchableOpacity>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
  button: {
    padding: 10,
    height: 100,
    width: 100,
    backgroundColor: '#12A',
    alignItems: 'center',
    justifyContent: 'center',
    margin: 20
  },
  label: {
    color: '#FFF',
  }
});

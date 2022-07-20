import React from 'react';
import { StatusBar } from 'expo-status-bar';
import { TouchableOpacity, StyleSheet, Text, View } from 'react-native';
import axios from 'axios';

const baseUrl = 'http://192.168.178.185';

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

      <Text style={styles.title}>
        Inclusion Life App
      </Text>

      <View style={styles.buttoncontainer}>
        <TouchableOpacity style={styles.button} onPress={onPress('F')}>
          <Text style={styles.label} >Frente</Text>
        </TouchableOpacity>
      </View>

      <View style={styles.buttoncontainer}>
        <TouchableOpacity style={styles.button} onPress={onPress('D')}>
          <Text style={styles.label} >Direita</Text>
        </TouchableOpacity>

        <TouchableOpacity style={styles.button} onPress={onPress('S')}>
          <Text style={styles.label}>Frear
          </Text>
        </TouchableOpacity>

        <TouchableOpacity style={styles.button} onPress={onPress('E')}>
          <Text style={styles.label}>Esquerda</Text>
        </TouchableOpacity>
      </View>

      <View style={styles.buttoncontainer}>
        <TouchableOpacity style={styles.button} onPress={onPress('T')}>
          <Text style={styles.label}>Trás</Text>
        </TouchableOpacity>
      </View>

    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#FFFF',
    alignItems: 'center',
    justifyContent: 'center',
  },
  button: {
    padding: 10,
    minHeight: 100,
    minWidth: 100,
    backgroundColor: '#AAA',
    alignItems: 'center',
    justifyContent: 'center',
    margin: 10,
    flex: 1,
  },
  buttoncontainer: {
    flexDirection: 'row',
    padding: 10,
  },
  label: {
    color: '#FFF',
    fontWeight: "bold",
    fontSize: 20,
  },
  title: {
    fontSize: 20,
    fontWeight: "bold",
    position: 'absolute',
    top: 60,
  }
});

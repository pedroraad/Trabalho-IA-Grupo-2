import { useEffect, useState } from "react";
import "./App.css";
import bfsData from "./resultBFS.json";
import dfsData from "./resultDFS.json";
import backtrackingData from "./resultbacktracking.json";
import Chessboard from "./Chessboard";

const dataByAlgorithm = {
  bfs: bfsData,
  dfs: dfsData,
  backtracking: backtrackingData,
};

const titleByAlgorithm = {
  bfs: "Busca em Profundidade",
  dfs: "Busca em Largura",
  backtracking: "Backtracking",
};

const App = () => {
  const [visibleMoviments, setVisibleMoviments] = useState([0]);
  const [index, setIndex] = useState(0);
  const [algorithm, setAlgorithm] = useState("bfs");
  const [currentBoardState, setCurrentBoardState] = useState();

  const resetState = () => {
    setIndex(0);
    const newVisibleMoviments = [0];

    const newState = dataByAlgorithm[algorithm]["24"].map((value) => {
      if (newVisibleMoviments.includes(value)) {
        return value;
      }

      return -1;
    });

    setVisibleMoviments(newVisibleMoviments);
    setCurrentBoardState(newState);
  };

  const handleNewBoardState = () => {
    setIndex((prevState) => prevState + 1);
    const newVisibleMoviments = [...visibleMoviments, index + 1];

    const newState = dataByAlgorithm[algorithm]["24"].map((value) => {
      if (newVisibleMoviments.includes(value)) {
        return value;
      }

      return -1;
    });

    setVisibleMoviments(newVisibleMoviments);
    setCurrentBoardState(newState);
  };

  const changeAlgorithm = () => {
    if (algorithm === "bfs") {
      setAlgorithm("dfs");
    } else if (algorithm === "dfs") {
      setAlgorithm("backtracking");
    } else setAlgorithm("bfs");
  };

  useEffect(() => {
    setCurrentBoardState(handleNewBoardState(0));
  }, []);

  useEffect(() => {
    resetState();
  }, [algorithm]);

  return (
    <div>
      <h1>{titleByAlgorithm[algorithm]}</h1>
      <Chessboard boardState={currentBoardState} />
      <button onClick={handleNewBoardState}>Proximo Estado</button>
      <button onClick={changeAlgorithm}> Mudar algoritmo </button>
    </div>
  );
};

export default App;

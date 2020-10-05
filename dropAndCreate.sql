-- Table: public."vertex"

-- DROP TABLE public."vertex";
DROP table if exists public.vertex;
CREATE TABLE public.vertex
(
    uID text NOT NULL primary key,
    region integer NOT NULL,
    area integer NOT NULL,
    id integer NOT NULL,
    info jsonb NOT NULL
)
WITH (
    OIDS = FALSE
)
TABLESPACE pg_default;

COMMENT ON TABLE public.vertex
    IS 'Описание вершин графа';
COMMENT ON COLUMN public.vertex.uID
    IS 'Уникальный ключ вершины вида RRRRRAAAAADDDDD';
COMMENT ON COLUMN public.vertex.region
    IS 'Регион';
COMMENT ON COLUMN public.vertex.area
    IS 'Район';
COMMENT ON COLUMN public.vertex.id
    IS 'Номер перекрестка';
COMMENT ON COLUMN public.vertex.info
    IS 'Информация';

-- DROP TABLE public.edges;
DROP table if exists public.edges;
CREATE TABLE public.edges
(
    uIDin text NOT NULL,
    uIDout text NOT NULL,
    region integer NOT NULL,
    info jsonb NOT NULL
)
WITH (
    OIDS = FALSE
)
TABLESPACE pg_default;

COMMENT ON TABLE public.edges
    IS 'Описание ребер графа';
COMMENT ON COLUMN public.edges.uIDin
    IS 'Вершина вход';
COMMENT ON COLUMN public.edges.uIDout
    IS 'Вершина выход';
COMMENT ON COLUMN public.edges.info
    IS 'Информация';

